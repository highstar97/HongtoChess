#pragma once

#include "GameFramework/Actor.h"
#include "HCThirdPartySocketServerActor.generated.h"

class FSocket;
UCLASS()
class HONGTOCHESS_API AHCThirdPartySocketServerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHCThirdPartySocketServerActor();

private:
	FSocket* ConnectionSocket = nullptr;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Start();
	void GetMessage();
};
