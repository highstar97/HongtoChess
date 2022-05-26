#include "Champion/BaseChampion.h"
#include "Champion/ChampionStatComponent.h"
#include "HCGameMode.h"
#include "HCGameState.h"
#include "Map/Tile.h"
#include "Map/MapData.h"
#include "Map/AdjancencyHexGridData.h"
#include "Skill/ChampionSkillComponent.h"
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

	PlayerNumber = 7;		// Need to delete ( this is for testing )
	LocationNumber = 50;	// Need to delete ( this is for testing )
}

void ABaseChampion::BeginPlay()
{
	Super::BeginPlay();

	SetOnTile(PlayerNumber, LocationNumber);
}

void ABaseChampion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AttackCoolTime += DeltaTime;
	if (AttackCoolTime >= 5/*1/ChampionStat->GetAttackSpeed()*/)
	{
		Attack();
		AttackCoolTime = 0;
	}
}

void ABaseChampion::SetOnTile(int32 _PlayerNumber, int32 _LocationNumber)
{
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
	else if (LocationNumber < 74)
	{
		// Is in Locker
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LocationNumber Error!"));
	}
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
	TileName += TEXT("HEX");
	TileName += FString::FromInt(_LocationNumber / 7 - 4);
	TileName += FString::FromInt(_LocationNumber % 7 + 1);
	for (AActor* tile : Tiles)
	{
		if (tile->GetName() == TileName)
		{
			this->SetActorLocation(tile->GetTransform().GetLocation() + FVector(0.0f, 0.0f, 20.0f));
			if (_PlayerNumber == 8)
			{
				this->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
			}
		}
	}

	auto HCGameState = Cast<AHCGameState>(UGameplayStatics::GetGameState(this));
	if (!HCGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseChampion Can't Access to HCGameState"));
		return;
	}
	HCGameState->GetMapData()->RecordChampionLocation(this, _LocationNumber);
}

void ABaseChampion::FindTarget()
{
	// BFSŽ�� �ϸ鼭 �߰� �� Target���� ���
	// ������ġ����  ��ĭ ������ ���� PlayerNumber�� �ٸ� Champion�� �ִ��� HCPlayerState->GetMapData()���� Ȯ��
	// �ִٸ� Target����, ���ٸ� �� ĭ �� ������ ���� Ž��
	auto HCGameMode = Cast<AHCGameMode>(GetWorld()->GetAuthGameMode());
	UAdjancencyHexGridData* AdjancencyHexGridData = HCGameMode->GetAdjancencyHexGridData();
	auto HCGameState = Cast<AHCGameState>(UGameplayStatics::GetGameState(this));
	if (!HCGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseChampion Can't Access to HCGameState"));
		return;
	}

	TQueue<int32> Queue;
	TArray<bool> Visited;
	Visited.Init(false, 56);

	Queue.Enqueue(LocationNumber);
	Visited[LocationNumber] = true;

	while (!Queue.IsEmpty())
	{
		int32 CurrentLocation = *Queue.Peek();
		//UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentLocation);
		for (int32 i = 0; i < AdjancencyHexGridData->GetAdjacencyHexGridData()[CurrentLocation].Num(); ++i)
		{
			int32 NextLocation = AdjancencyHexGridData->GetAdjacencyHexGridData()[CurrentLocation][i];
			Target = HCGameState->GetMapData()->IsTarget(PlayerNumber, NextLocation);
			if (nullptr != Target)
			{
				//UE_LOG(LogTemp, Log, TEXT("%d"), NextLocation);
				//UE_LOG(LogTemp, Log, TEXT("%s"), *(Target->GetName()));
				return;
			}

			if (Visited[NextLocation] == false)
			{
				Queue.Enqueue(NextLocation);
				Visited[NextLocation] = true;
			}
		}
		Queue.Pop();
	}
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
		UE_LOG(LogTemp, Warning, TEXT("%s FindTarget!, Target is %s"), *GetName(), *(Target->GetName()));
		if (CanAttack())
		{
			// Attack ���
		}
		else
		{
			MoveToTarget();
		}
	}
	else
	{
		FindTarget();
	}
}

bool ABaseChampion::CanAttack()
{
	// Target���� �Ÿ��� ��Ÿ� ���
	// 
	return false;
}