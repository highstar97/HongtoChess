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

void UMapData::RecordChampionLocation(ABaseChampion* Champion, int32 LocationNumber)
{
	HexGridData[LocationNumber / 7][LocationNumber % 7] = Champion;
}

ABaseChampion* UMapData::IsTarget(int32 MyPlayerNumber, int32 LocationNumber)
{
	ABaseChampion* Suspect = HexGridData[LocationNumber / 7][LocationNumber % 7];
	if (nullptr == Suspect)
	{
		return nullptr;
	}
	else
	{
		if (MyPlayerNumber != Suspect->GetPlayerNumber())
		{
			return Suspect;
		}
		return nullptr;
	}
}