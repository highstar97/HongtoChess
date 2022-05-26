#pragma once

#include "UObject/NoExportTypes.h"
#include "AdjancencyHexGridData.generated.h"

UCLASS()
class HONGTOCHESS_API UAdjancencyHexGridData : public UObject
{
	GENERATED_BODY()

public:
	UAdjancencyHexGridData();
	
	TArray<TArray<int32>> GetAdjacencyHexGridData() { return AdjacencyHexGridData; }

private:
	TArray<TArray<int32>> AdjacencyHexGridData;
};
