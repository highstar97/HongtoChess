#include "HCGameInstance.h"

UHCGameInstance::UHCGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HCSTAT(TEXT("/Game/GameData/HCStatData.HCStatData"));
	if (DT_HCSTAT.Succeeded())
	{
		HCStatDataTable = DT_HCSTAT.Object;
	}
	if (HCStatDataTable->GetRowMap().Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("HCStatDataTable has NO data!"));
	}
}

FHCStatData* UHCGameInstance::GetHCStatData(int32 SerialNumber)
{
	return HCStatDataTable->FindRow<FHCStatData>(*FString::FromInt(SerialNumber),TEXT(""));
}