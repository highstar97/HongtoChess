#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BaseChampion.generated.h"

class UTexture2D;
class UChampionStatComponent;
class UChampionSkillComponent;

UENUM()
enum class ECountry : uint8
{
	WE,
	CHOCK,
	OH,
	HAN,
	NONE
};

UENUM()
enum class ESynergy : uint8
{
	DOWONGYEOLUI,
	GWANUFANCLUB
};

UCLASS()
class HONGTOCHESS_API ABaseChampion : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseChampion();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	int32 GetPlayerNumber() { return PlayerNumber; }

	void SetOnTile(int32 _PlayerNumber, int32 _LocationNumber);
	void SetOnHexTile(int32 _PlayerNumber, int32 _LocationNumber);

	void FindTarget();
	void MoveToTarget();
	void Attack();
	bool CanAttack();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Champion")
	int32 SerialNumber;

	UPROPERTY(EditInstanceOnly, Category = "Champion")
	int32 PlayerNumber;

	UPROPERTY(VisibleDefaultsOnly, Category = "Champion")
	FString Name;

	UPROPERTY(VisibleDefaultsOnly, Category = "Champion")
	int32 Cost;

	UPROPERTY(EditAnywhere, Category = "Champion")
	int32 Star;

	UPROPERTY(VisibleDefaultsOnly, Category = "Champion")
	ECountry Country;

	UPROPERTY(VisibleDefaultsOnly, Category = "Champion")
	TArray<ESynergy> Synergy;

	UPROPERTY(EditAnywhere, Category = "Stat")
	UChampionStatComponent* ChampionStat;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Skill")
	UChampionSkillComponent* ChampionSkill;

	//UPROPERTY(EditAnywhere, Category = "Item")
	//TArray<UItem*> Item;

	UPROPERTY(EditAnywhere, Category = "Map")
	int32 LocationNumber = -1;

	float AttackCoolTime = 0.0f;

	ABaseChampion* Target = nullptr;
};