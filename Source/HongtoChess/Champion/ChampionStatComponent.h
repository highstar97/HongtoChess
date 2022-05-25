#pragma once

#include "Components/ActorComponent.h"
#include "ChampionStatComponent.generated.h"

struct FHCStatData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONGTOCHESS_API UChampionStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UChampionStatComponent();

protected:
	virtual void BeginPlay() override;

public:
	void UpgradeStat();

	void InitStatData(int SerialNumber);

	float GetAttackSpeed();
	int32 GetRange();

public:
	FHCStatData* CurrentStatData = nullptr;

private:
	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 CurrentHP;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 MaxHP;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 CurrentMP;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 MaxMP;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 AttackDamage;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 AbilityPower;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Defense;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 MagicResistance;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	float AttackSpeed;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Range;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CriticalRate;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CriticalCoefficient;
};
