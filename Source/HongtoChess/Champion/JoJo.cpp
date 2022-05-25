#include "Champion/JoJo.h"
#include "Skill/JoJoSkill.h"
#include "Champion/ChampionStatComponent.h"
#include "Skill/ChampionSkillComponent.h"

AJoJo::AJoJo()
{
	SerialNumber = 1;
	Name = TEXT("JoJo");
	Cost = 5;
	Star = 1;
	Country = ECountry::WE;
	Synergy.Emplace(ESynergy::GWANUFANCLUB);
	ChampionSkill = CreateDefaultSubobject<UJoJoSkill>(TEXT("CHAMPIONSKILL"));
}

void AJoJo::BeginPlay()
{
	Super::BeginPlay();

	ChampionStat->InitStatData(SerialNumber);
	ChampionSkill->InitSkillData(SerialNumber);
}