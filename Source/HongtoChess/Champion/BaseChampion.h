#pragma once

#include "GameFramework/Character.h"
#include "BaseChampion.generated.h"

class UTexture2D;
class UChampionStatComponent;

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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	
	//UPROPERTY(VisibleDefaultsOnly, Category = "Skill")
	//USkill Skill;

	//UPROPERTY(EditAnywhere, Category = "Item")
	//TArray<UItem*> Item;
};