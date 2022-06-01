#pragma once

#include "GameFramework/PlayerState.h"
#include "HCPlayerState.generated.h"

class UMapData;

UCLASS()
class HONGTOCHESS_API AHCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AHCPlayerState();

	void InitPlayerState();

private:
	UPROPERTY()
	int32 Health;
};
