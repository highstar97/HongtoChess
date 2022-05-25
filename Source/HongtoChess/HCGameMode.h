#pragma once

#include "GameFramework/GameModeBase.h"
#include "HCGameMode.generated.h"

class AHCThirdPartySocketServerActor;

UCLASS()
class HONGTOCHESS_API AHCGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHCGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	AHCThirdPartySocketServerActor* GetTPSocket() { return TPSocket; }

private:
	UPROPERTY()
	int32 BigRound;

	UPROPERTY()
	int32 SmallRound;

	UPROPERTY()
	AHCThirdPartySocketServerActor* TPSocket;
};
