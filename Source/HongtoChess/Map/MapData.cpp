#include "Map/MapData.h"
#include "../Champion/BaseChampion.h"

UMapData::UMapData()
{
	HexGridData.SetNumZeroed(8);
	for (int32 i = 0; i < HexGridData.Num(); ++i)
	{
		HexGridData[i].SetNumZeroed(7);
	}

	MyChampionLocker.Empty(0);
	EnemyChampionLocker.Empty(0);

	MyInterest = 0;
	EnemyInterest = 0;
}