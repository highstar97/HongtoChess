#include "Champion/BaseChampion.h"
#include "Champion/ChampionStatComponent.h"
#include "Map/Tile.h"
#include "Map/AdjancencyHexGridData.h"
#include "Skill/ChampionSkillComponent.h"
#include "HCAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"

ABaseChampion::ABaseChampion() : SerialNumber(0), PlayerNumber(0), Name(TEXT("None")), Cost(0), Star(0), Country(ECountry::NONE)
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANNEQUIN(TEXT("/Game/ARPG_Warrior/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_MANNEQUIN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MANNEQUIN.Object);
	}

	Synergy.Empty();
	ChampionStat = CreateDefaultSubobject<UChampionStatComponent>(TEXT("CHAMPIONSTAT"));
	ChampionSkill = nullptr;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> BASECHARACTER_ANIM(TEXT("/Game/Blueprint/Animation/CharacterAnimBlueprint.CharacterAnimBlueprint_C"));
	if (BASECHARACTER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BASECHARACTER_ANIM.Class);
	}

	IsAttacking = false;
}

void ABaseChampion::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerNumber = 1;		// Need to delete ( this is for testing )
	LocationNumber = 50;	// Need to delete ( this is for testing )

	if (LocationNumber < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LocationNumber Error!"));
	}
	else if (LocationNumber < 56)
	{
		// Is in field
		// Set Location by PlayerNumber
		SetOnHexTile(PlayerNumber, LocationNumber);
	}
	else if(LocationNumber < 74)
	{
		// Is in Locker
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LocationNumber Error!"));
	}
}

void ABaseChampion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AttackCoolTime += DeltaTime;
	if (AttackCoolTime >= 1/*1/ChampionStat->GetAttackSpeed()*/)
	{
		Attack();
		AttackCoolTime = 0;
	}
}

void ABaseChampion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseChampion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HCAnim = Cast<UHCAnimInstance>(GetMesh()->GetAnimInstance());
	if (!HCAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("no HCAnim"));
	}

	HCAnim->OnMontageEnded.AddDynamic(this, &ABaseChampion::OnAttackMontageEnded);

}

void ABaseChampion::SetOnHexTile(int32 _PlayerNumber, int32 _LocationNumber)
{
	TArray<AActor*> Tiles;
	TSubclassOf<class ATile> FindClassType;
	FindClassType = ATile::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), FindClassType, Tiles);

	FString TileName;
	TileName += TEXT("PC");
	TileName += FString::FromInt(_PlayerNumber);
	TileName += FString::FromInt(_LocationNumber / 7 - 4);
	TileName += FString::FromInt(_LocationNumber % 7 + 1);
	for (AActor* tile : Tiles)
	{
		if (tile->GetName() == TileName)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tile->GetName()));
			this->SetActorLocation(tile->GetTransform().GetLocation() + FVector(0.0f, 0.0f, 20.0f));
		}
	}
}

void ABaseChampion::FindTarget()
{
	// BFSŽ�� �ϸ鼭 �߰� �� Target���� ���

}

void ABaseChampion::MoveToTarget()
{
	// Target�� ��ġ�� ����Ǿ����� Ȯ��
	// �̵�
}

void ABaseChampion::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Attack!"), *GetName());
	if (Target)
	{
		if (CanAttack())
		{
			if (IsAttacking)
			{
				return;
			}
			
			HCAnim->PlayAttackMontage(ChampionStat->GetAttackSpeed());
			IsAttacking = true;
		}
		else
		{
			MoveToTarget();
		}
	}
	else
	{
		FindTarget();
		HCAnim->PlayAttackMontage(ChampionStat->GetAttackSpeed());
		IsAttacking = true;
	}
}

bool ABaseChampion::CanAttack()
{
	// Target���� �Ÿ��� ��Ÿ� ���
	// 
	return false;
}

void ABaseChampion::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!IsAttacking)
	{
		return;
	}
	IsAttacking = false;
}
