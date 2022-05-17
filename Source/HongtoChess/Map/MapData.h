#pragma once

#include "UObject/NoExportTypes.h"
#include "MapData.generated.h"

class UBaseChampion;

UCLASS()
class HONGTOCHESS_API UMapData : public UObject
{
	GENERATED_BODY()

public:
	UMapData();

public:
	TArray<TArray<int32>> AdjacencyHexGridData;

	TArray<TArray<UBaseChampion*>> HexGridData;

	TArray<UBaseChampion*> MyChampionLocker;

	int MyInterest;

	TArray<UBaseChampion*> EnemyChampionLocker;

	int EnemyInterest;
};
