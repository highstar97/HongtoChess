#pragma once

#include "CoreMinimal.h"
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	virtual void UseSkill();
	FString getSkillName();
	FString getSkillInfo();
	void InitSkillData(int SerialNumber);

public:
	FHCSkillData* CurrentSkillData = nullptr;

private:
	UPROPERTY(VisibleAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	FString SkillName;

	UPROPERTY(VisibleAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	FString SkillInfo;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 CurrentHP;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 MaxHP;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 CurrentMP;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 MaxMP;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 AttackDamage;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 AbilityPower;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 Defense;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 MagicResistance;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	float AttackSpeed;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 Range;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	float CriticalRate;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	float CriticalCoefficient;

	UPROPERTY(Transient, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = true))
	int32 DefaultSkillDamage;
};
