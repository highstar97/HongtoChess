#pragma once

#include "UObject/NoExportTypes.h"
#include "AdjancencyHexGridData.generated.h"

UCLASS()
class HONGTOCHESS_API UAdjancencyHexGridData : public UObject
{
	GENERATED_BODY()

public:
	UAdjancencyHexGridData();
	
public:
	TArray<TArray<int32>> AdjacencyHexGridData;
};
