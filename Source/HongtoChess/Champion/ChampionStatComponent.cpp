#include "Champion/ChampionStatComponent.h"
#include "HCGameInstance.h"
#include "Kismet/GameplayStatics.h"

UChampionStatComponent::UChampionStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHP = 0;
	MaxHP = 0;
	CurrentMP = 0;
	MaxMP = 0;
	AttackDamage = 0;
	AbilityPower = 0;
	Defense = 0;
	MagicResistance = 0;
	AttackSpeed = 1.0f;	
	Range = 1;
	CriticalRate = 0.0f;
	CriticalCoefficient = 0.0f;
}

void UChampionStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UChampionStatComponent::UpgradeStat()
{
	MaxHP *= 1.8;
	CurrentHP = MaxHP;

	AttackDamage *= 1.8;
}

void UChampionStatComponent::InitStatData(int SerialNumber)
{
	// 엑셀 데이터에서 SerialNumber에 맞는 데이터를 불러와서 1성 Stat에 대입
	UHCGameInstance* HCGameInstance = Cast<UHCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == HCGameInstance)
	{
		return;
	}

	CurrentStatData = HCGameInstance->GetHCStatData(SerialNumber);
	if (nullptr != CurrentStatData)
	{
		MaxHP = CurrentStatData->MaxHP;
		CurrentHP = MaxHP;
		MaxMP = CurrentStatData->MaxMP;
		CurrentMP = CurrentStatData->CurrentMP;
		AttackDamage = CurrentStatData->AttackDamage;
		AbilityPower = CurrentStatData->AbilityPower;
		Defense = CurrentStatData->Defense;
		MagicResistance = CurrentStatData->MagicResistance;
		AttackSpeed = CurrentStatData->AttackSpeed;
		Range = CurrentStatData->Range;
		CriticalRate = CurrentStatData->CriticalRate;
		CriticalCoefficient = CurrentStatData->CriticalCoefficient;return;
	}
}

float UChampionStatComponent::GetAttackSpeed()
{
	return AttackSpeed;
}

int32 UChampionStatComponent::GetRange()
{
	return Range;
}
