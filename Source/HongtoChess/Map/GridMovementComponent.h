#pragma once

#include "Components/ActorComponent.h"
#include "GridMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONGTOCHESS_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGridMovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<TArray<int32>> GridGraphData;
};
