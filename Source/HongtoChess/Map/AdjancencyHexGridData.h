#pragma once

#include "UObject/NoExportTypes.h"
#include "AdjancencyHexGridData.generated.h"

UCLASS()
class HONGTOCHESS_API UAdjancencyHexGridData : public UObject
{
	GENERATED_BODY()

public:
	UAdjancencyHexGridData();

	void InitAdjancencyHexGridData();
	void InitDistanceData();

	TArray<TArray<int32>> GetAdjancencyHexGridData() { return AdjancencyHexGridData; }

	int32 GetDistanceAtoB(int32 LocationA, int32 LocationB);

private:
	TArray<TArray<int32>> AdjancencyHexGridData;

	TMap<int32, TArray<TArray<int32>>> DistanceData;
};