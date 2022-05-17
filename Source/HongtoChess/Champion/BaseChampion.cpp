#include "Champion/BaseChampion.h"
#include "Champion/ChampionStatComponent.h"
#include "Skill/ChampionSkillComponent.h"
#include "Engine/Texture2D.h"

ABaseChampion::ABaseChampion() : SerialNumber(0), PlayerNumber(0), Name(TEXT("None")), Cost(0), Star(0), Country(ECountry::NONE)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANNEQUIN(TEXT("/Game/ARPG_Warrior/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_MANNEQUIN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MANNEQUIN.Object);
	}

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

// Find Target
// Loop[ Can Attack ? Attack : Move To Target ]
// Attack = Is Dead ? Find Target : Attack
void ABaseChampion::FindTarget()
{
	
}