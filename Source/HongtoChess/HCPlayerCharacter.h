#pragma once

#include "GameFramework/Character.h"
#include "HCPlayerCharacter.generated.h"

UCLASS()
class HONGTOCHESS_API AHCPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHCPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Test();
};
