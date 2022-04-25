#include "HCSkillGameInstance.h"

UHCSkillGameInstance::UHCSkillGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HCSKILL(TEXT("/Game/GameData/skilldata.skilldata"));
	if (DT_HCSKILL.Succeeded())
	{
		HCSkillDataTable = DT_HCSKILL.Object;
	}
	if (HCSkillDataTable->GetRowMap().Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("HCSkillDataTable has NO data!"));
	}
}

FHCSkillData* UHCSkillGameInstance::GetHCSkillData(int32 SerialNumber)
{
	return HCSkillDataTable->FindRow<FHCSkillData>(*FString::FromInt(SerialNumber), TEXT(""));
}