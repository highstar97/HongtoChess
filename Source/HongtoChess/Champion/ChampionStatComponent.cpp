#include "Champion/ChampionStatComponent.h"

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
	AttackSpeed = 0.0f;
	Range = 0;
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
	
}