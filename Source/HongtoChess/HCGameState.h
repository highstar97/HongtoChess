#pragma once

#include "GameFramework/GameStateBase.h"
#include "HCGameState.generated.h"

class UMapData;

UCLASS()
class HONGTOCHESS_API AHCGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AHCGameState();

	UMapData* GetMapData() { return MapData; }

	void InitGameState();

private:
	UPROPERTY()
	UMapData* MapData = nullptr;
};
