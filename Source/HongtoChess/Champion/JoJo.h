#pragma once

#include "Champion/BaseChampion.h"
#include "JoJo.generated.h"

UCLASS()
class HONGTOCHESS_API AJoJo : public ABaseChampion
{
	GENERATED_BODY()

public:
	AJoJo();

	virtual void BeginPlay();
};
