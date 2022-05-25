#pragma once

#include "GameFramework/PlayerController.h"
#include "HCPlayerController.generated.h"

UCLASS()
class HONGTOCHESS_API AHCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	virtual void SetupInputComponent() override;

	void Test();
};
