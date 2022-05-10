#pragma once

#include "GameFramework/GameModeBase.h"
#include "HCGameMode.generated.h"

UCLASS()
class HONGTOCHESS_API AHCGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHCGameMode();

private:
	UPROPERTY()
	int32 BigRound;

	UPROPERTY()
	int32 SmallRound;
};
