#include "HCGameState.h"
#include "Map/MapData.h"

AHCGameState::AHCGameState()
{
	InitGameState();
}

void AHCGameState::InitGameState()
{
	MapData = NewObject<UMapData>();
}