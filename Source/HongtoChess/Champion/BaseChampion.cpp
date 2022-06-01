#include "Champion/BaseChampion.h"
#include "Champion/ChampionStatComponent.h"
#include "HCGameMode.h"
#include "HCGameState.h"
#include "Map/Tile.h"
#include "Map/MapData.h"
#include "Map/AdjancencyHexGridData.h"
#include "Skill/ChampionSkillComponent.h"
#include "HCAnimInstance.h"
#include "Components/CapsuleComponent.h"//
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"						// TActorIterator
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

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("BaseChampion"));
	PlayerNumber = 7;		// Need to delete ( this is for testing )
	LocationNumber = 50;	// Need to delete ( this is for testing )
}

void ABaseChampion::BeginPlay()
{
	Super::BeginPlay();

	SetOnTile(LocationNumber);	// Need to delete ( this is for testing )
}

void ABaseChampion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AttackCoolTime += DeltaTime;
	if (AttackCoolTime >= 3)//1/ChampionStat->GetAttackSpeed())
	{
		Attack();
		AttackCoolTime = 0;
	}
}

void ABaseChampion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HCGameMode = Cast<AHCGameMode>(GetWorld()->GetAuthGameMode());
	if (!HCGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseChampion Can't Access to HCGameMode"));
	}
	HCGameState = Cast<AHCGameState>(UGameplayStatics::GetGameState(this));
	if (!HCGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseChampion Can't Access to HCGameState"));
	};
	HCAnim = Cast<UHCAnimInstance>(GetMesh()->GetAnimInstance());
	if (!HCAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("no HCAnim"));
	}

	HCAnim->OnMontageEnded.AddDynamic(this, &ABaseChampion::OnAttackMontageEnded);
}

void ABaseChampion::SetOnTile(int32 _LocationNumber)
{
	if (LocationNumber < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LocationNumber Error!"));
	}
	else if (LocationNumber < 56)
	{
		// Is in field
		// Set Location by PlayerNumber
		SetOnHexTile(LocationNumber);
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

void ABaseChampion::SetOnHexTile(int32 _LocationNumber)
{
	FString TileName;
	TileName += TEXT("PC");
	TileName += FString::FromInt(PlayerNumber);
	TileName += TEXT("HEX");
	TileName += FString::FromInt(_LocationNumber / 7 - 4);
	TileName += FString::FromInt(_LocationNumber % 7);
	for (TActorIterator<ATile> It(GetWorld()); It; ++It)
	{
		if (It->GetName() == TileName)
		{
			this->SetActorLocation(It->GetTransform().GetLocation() + FVector(0.0f, 0.0f, 20.0f));
			if (PlayerNumber == 8)
			{
				this->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
			}
		}
	}

	HCGameState->GetMapData()->RecordChampionLocation(this, _LocationNumber);
	LocationNumber = _LocationNumber;
}

void ABaseChampion::FindTarget()
{
	// BFS탐색 하면서 발견 시 Target으로 삼기
	// 현재위치에서  한칸 떨어진 곳에 PlayerNumber가 다른 Champion이 있는지 HCPlayerState->GetMapData()에서 확인
	// 있다면 Target으로, 없다면 한 칸 더 떨어진 곳을 탐색
	UAdjancencyHexGridData* AdjancencyHexGridData = HCGameMode->GetAdjancencyHexGridData();

	TQueue<int32> Queue;
	TArray<bool> Visited;
	Visited.Init(false, 56);

	Queue.Enqueue(LocationNumber);
	Visited[LocationNumber] = true;

	while (!Queue.IsEmpty())
	{
		int32 CurrentLocation = *Queue.Peek();
		//UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentLocation);
		for (int32 i = 0; i < AdjancencyHexGridData->GetAdjancencyHexGridData()[CurrentLocation].Num(); ++i)
		{
			int32 NextLocation = AdjancencyHexGridData->GetAdjancencyHexGridData()[CurrentLocation][i];
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
	// Target의 위치가 변경되었는지 확인
	// 최단거리 탐색 -> 이동
	int32 Destination = HCGameState->GetMapData()->GetTargetLocationNumber(Target);
	if (-1 == Destination)	// Target is Dead? or Can't Attack
	{
		FindTarget();
	}
	Move(GetNextTileToMove(Destination));
}

void ABaseChampion::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Attack!"), *GetName());
	if (Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Find Target!, Target is %s"), *GetName(), *(Target->GetName()));
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
	}
}

bool ABaseChampion::CanAttack()
{
	// Target과의 거리와 사거리 고려
	int32 Range = ChampionStat->GetRange();
	int32 TargetLocationNumber = HCGameState->GetMapData()->GetTargetLocationNumber(Target);
	if (Range >= HCGameMode->GetAdjancencyHexGridData()->GetDistanceAtoB(LocationNumber, TargetLocationNumber))
	{
		return true;
	}
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

int32 ABaseChampion::GetNextTileToMove(int32 Destination)
{
	UAdjancencyHexGridData* AdjancencyHexGridData = HCGameMode->GetAdjancencyHexGridData();
	int32 NextTile = -1;
	int32 Min = 1000;
	for (int32 i = 0; i < AdjancencyHexGridData->GetAdjancencyHexGridData()[LocationNumber].Num(); ++i)
	{
		int32 AdjancencyLocation = AdjancencyHexGridData->GetAdjancencyHexGridData()[LocationNumber][i];
		if (HCGameState->GetMapData()->IsCanMoveTile(AdjancencyLocation))
		{
			// AdjancencyLocation -> Destination 최단거리 구해서 DistanceToDestination에 저장
			int32 Value = AdjancencyHexGridData->GetDistanceAtoB(AdjancencyLocation, Destination);
			if (Min > Value)
			{
				Min = Value;
				NextTile = AdjancencyLocation;
			}
		}
	}

	return NextTile;
}

void ABaseChampion::Move(int32 NextLocationNumber)
{
	if (-1 == NextLocationNumber)
	{
		return;	// Can't Move Because of Other Champions
	}

	UE_LOG(LogTemp, Warning, TEXT("%s Move : %d -> %d"),*GetName(), LocationNumber, NextLocationNumber);
	HCGameState->GetMapData()->UnRecordChampionLocation(LocationNumber);
	LocationNumber = NextLocationNumber;
	// NextTileLocation을 향해 회전
	// NextTileLocation을 향해 이동
	int32 Number = LocationNumber / 7 - 4 >= 0 ? 7 : 8;
	FString TileName;
	TileName += TEXT("PC");
	TileName += FString::FromInt(Number);
	TileName += TEXT("HEX");
	TileName += FString::FromInt(LocationNumber / 7 - 4);
	TileName += FString::FromInt(LocationNumber % 7);
	for (TActorIterator<ATile> It(GetWorld()); It; ++It)
	{
		if (It->GetName() == TileName)
		{
			this->SetActorLocation(It->GetTransform().GetLocation() + FVector(0.0f, 0.0f, 20.0f));
			if (PlayerNumber == 8)
			{
				this->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
			}
		}
	}
	HCGameState->GetMapData()->RecordChampionLocation(this, NextLocationNumber);
}
