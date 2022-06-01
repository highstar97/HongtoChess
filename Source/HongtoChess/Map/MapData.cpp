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

void UMapData::UnRecordChampionLocation(int32 LocationNumber)
{
	HexGridData[LocationNumber / 7][LocationNumber % 7] = nullptr;
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

int32 UMapData::GetTargetLocationNumber(ABaseChampion* Target)
{
	for (int32 i = 0; i < HexGridData.Num(); ++i)
	{
		for (int32 j = 0; j < HexGridData[i].Num(); ++j)
		{
			if (Target == HexGridData[i][j])
			{
				return i * 7 + j;
			}
		}
	}
	return -1; // Can't Find Target, Because Target is Dead? or Can't Attack.
}

bool UMapData::IsCanMoveTile(int32 LocationNumber)
{
	ABaseChampion* Destination = HexGridData[LocationNumber / 7][LocationNumber % 7];
	if (nullptr == Destination)
	{
		return true;
	}
	else
	{
		return false;
	}
}