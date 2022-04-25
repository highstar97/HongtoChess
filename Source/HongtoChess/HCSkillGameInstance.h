#pragma once

#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "HCSkillGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FHCSkillData : public FTableRowBase
{
	GENERATED_BODY()


public:
	FHCSkillData() : MaxHP(100), CurrentMP(0), MaxMP(100), AttackDamage(10), AbilityPower(100), Defense(10), MagicResistance(10), AttackSpeed(1.0f), Range(1), CriticalRate(0.25f), CriticalCoefficient(1.5f), DefaultSkillDamage(100) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 MaxHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 CurrentMP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 MaxMP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 AttackDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 AbilityPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 Defense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 MagicResistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	float AttackSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	float CriticalRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	float CriticalCoefficient;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillData")
	int32 DefaultSkillDamage;
};

UCLASS()
class HONGTOCHESS_API UHCSkillGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UHCSkillGameInstance();

	FHCSkillData* GetHCSkillData(int32 SerialNumber);

private:
	UPROPERTY()
	UDataTable* HCSkillDataTable;
};