#include "Champion/JoJo.h"
#include "Champion/ChampionStatComponent.h"

AJoJo::AJoJo()
{
	SerialNumber = 1;
	Name = TEXT("JoJo");
	Cost = 5;
	Star = 1;
	Country = ECountry::WE;
	Synergy.Emplace(ESynergy::GWANUFANCLUB);
	ChampionStat->InitStatData(SerialNumber);
}