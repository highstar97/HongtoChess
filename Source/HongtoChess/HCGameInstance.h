#pragma once

#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "HCGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FHCStatData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FHCStatData() : MaxHP(100), CurrentMP(0), MaxMP(100), AttackDamage(10), AbilityPower(100), Defense(10), MagicResistance(10), AttackSpeed(1.0f), Range(1), CriticalRate(0.25f), CriticalCoefficient(1.5f) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 MaxHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 CurrentMP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 MaxMP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 AttackDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 AbilityPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 Defense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 MagicResistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	float AttackSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	int32 Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	float CriticalRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StatData")
	float CriticalCoefficient;
};

UCLASS()
class HONGTOCHESS_API UHCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UHCGameInstance();

	FHCStatData* GetHCStatData(int32 SerialNumber);

private:
	UPROPERTY()
	UDataTable* HCStatDataTable;
};
