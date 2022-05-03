#pragma once

#include "Skill/ChampionSkillComponent.h"
#include "JoJoSkill.generated.h"

UCLASS()
class HONGTOCHESS_API UJoJoSkill : public UChampionSkillComponent
{
	GENERATED_BODY()

public:
	UJoJoSkill();

	virtual void UseSkill() override;
};