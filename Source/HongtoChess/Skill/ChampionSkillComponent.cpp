#include "Skill/ChampionSkillComponent.h"
#include "HCGameInstance.h"
#include "Kismet/GameplayStatics.h"

UChampionSkillComponent::UChampionSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Name = TEXT("DefaultName");
	Explanation = TEXT("DefaultExp");
	DefaultDamage = 0;
}

void UChampionSkillComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UChampionSkillComponent::InitSkillData(int SerialNumber)
{
	UHCGameInstance* HCGameInstance = Cast<UHCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == HCGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("HCSkill null"));
		return;
	}

	CurrentSkillData = HCGameInstance->GetHCSkillData(SerialNumber);
	if (nullptr != CurrentSkillData)
	{
		Name = CurrentSkillData->Name;
		Explanation = CurrentSkillData->Explanation;
		DefaultDamage = CurrentSkillData->DefaultDamage;
		return;
	}
}

void UChampionSkillComponent::UseSkill()
{

}

FString UChampionSkillComponent::GetName()
{
	return Name;
}

FString UChampionSkillComponent::GetExplanation()
{
	return Explanation;
}

int32 UChampionSkillComponent::GetDefaultDamage()
{
	return DefaultDamage;
}