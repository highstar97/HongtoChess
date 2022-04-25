#pragma once

#include "Components/ActorComponent.h"
#include "ChampionSkillComponent.generated.h"

struct FHCSkillData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONGTOCHESS_API UChampionSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UChampionSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void InitSkillData(int SerialNumber);
	virtual void UseSkill();
	FString GetName();
	FString GetExplanation();
	int32 GetDefaultDamage();

public:
	FHCSkillData* CurrentSkillData = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	FString Explanation;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 DefaultDamage;
};
