#include "HCSkillGameInstance.h"
#include "Champion/ChampionSkillComponent.h"
#include "Kismet/GameplayStatics.h"

UChampionSkillComponent::UChampionSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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
	DefaultSkillDamage = 0;
}

void UChampionSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentMP == 100)
	{
		UE_LOG(LogTemp, Error, TEXT("skill used"));
		CurrentMP = 0;
	}
}

void UChampionSkillComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UChampionSkillComponent::InitSkillData(int SerialNumber)
{
	UHCSkillGameInstance* HCSkillGameInstance = Cast<UHCSkillGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == HCSkillGameInstance)
	{
		return;
	}

	CurrentSkillData = HCSkillGameInstance->GetHCSkillData(SerialNumber);
	if (nullptr != CurrentSkillData)
	{
		MaxHP = CurrentSkillData->MaxHP;
		CurrentHP = MaxHP;
		MaxMP = CurrentSkillData->MaxMP;
		CurrentMP = CurrentSkillData->CurrentMP;
		AttackDamage = CurrentSkillData->AttackDamage;
		AbilityPower = CurrentSkillData->AbilityPower;
		Defense = CurrentSkillData->Defense;
		MagicResistance = CurrentSkillData->MagicResistance;
		AttackSpeed = CurrentSkillData->AttackSpeed;
		Range = CurrentSkillData->Range;
		CriticalRate = CurrentSkillData->CriticalRate;
		CriticalCoefficient = CurrentSkillData->CriticalCoefficient;
		DefaultSkillDamage = CurrentSkillData->DefaultSkillDamage;
		return;
	}
}

void UChampionSkillComponent::UseSkill()
{
	/*if (CurrentMP == 100)
	{
		UE_LOG(LogTemp, Error, TEXT("skill used"));
		CurrentMP = 0;
	}*/
}

FString UChampionSkillComponent::getSkillName()
{
	return SkillName;
}

FString UChampionSkillComponent::getSkillInfo()
{
	return SkillInfo;
}