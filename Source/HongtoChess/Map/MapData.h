#pragma once

#include "UObject/NoExportTypes.h"
#include "MapData.generated.h"

class ABaseChampion;

UCLASS()
class HONGTOCHESS_API UMapData : public UObject
{
	GENERATED_BODY()

public:
	UMapData();

	void RecordChampionLocation(ABaseChampion* Champion, int32 LocationNumber);
	ABaseChampion* IsTarget(int32 MyPlayerNumber, int32 LocationNumber);

public:
	TArray<TArray<ABaseChampion*>> HexGridData;

	TArray<ABaseChampion*> MyChampionLocker;

	int MyInterest;

	TArray<ABaseChampion*> EnemyChampionLocker;

	int EnemyInterest;
};
