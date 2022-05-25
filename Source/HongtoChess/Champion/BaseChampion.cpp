#include "Champion/BaseChampion.h"
#include "Champion/ChampionStatComponent.h"
#include "Skill/ChampionSkillComponent.h"
#include "Engine/Texture2D.h"

ABaseChampion::ABaseChampion() : SerialNumber(0), PlayerNumber(0), Name(TEXT("None")), Cost(0), Star(0), Country(ECountry::NONE)
{
	Synergy.Empty();
	ChampionStat = CreateDefaultSubobject<UChampionStatComponent>(TEXT("CHAMPIONSTAT"));
	ChampionSkill = nullptr;
}

void ABaseChampion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseChampion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}