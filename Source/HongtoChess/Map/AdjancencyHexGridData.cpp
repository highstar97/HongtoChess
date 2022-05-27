#include "Map/AdjancencyHexGridData.h"

UAdjancencyHexGridData::UAdjancencyHexGridData()
{
	InitAdjancencyHexGridData();
	InitDistanceData();
}

void UAdjancencyHexGridData::InitAdjancencyHexGridData()
{
	int32 x = -4;
	int32 y = 0;
	AdjancencyHexGridData.SetNum(56);
	for (int32 i = 0; i < AdjancencyHexGridData.Num(); ++i)
	{
		AdjancencyHexGridData[i].Empty();

		int32 NodeNumber;
		// Even (x - 1, y), (x, y + 1), (x + 1, y), (x + 1, y - 1), (x, y - 1), (x - 1, y - 1)
		// Odd (x - 1, y + 1), (x, y + 1), (x + 1, y + 1), (x + 1, y), (x, y - 1), (x - 1, y)
		for (int32 j = 0; j < 6; ++j)
		{
			switch (j)
			{
			case(0):
			{
				if ((x + 4) % 2 == 0)
				{
					if (x - 1 >= -4)
					{
						NodeNumber = (x + 3) * 7 + y;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x - 1 >= -4 && y + 1 <= 6)
					{
						NodeNumber = (x + 3) * 7 + y + 1;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				break;
			}
			case(1):
			{
				if (y + 1 <= 6)
				{
					NodeNumber = (x + 4) * 7 + y + 1;
					AdjancencyHexGridData[i].Emplace(NodeNumber);
				}
				break;
			}
			case(2):
			{
				if ((x + 4) % 2 == 0)
				{
					if (x + 1 <= 3)
					{
						NodeNumber = (x + 5) * 7 + y;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x + 1 <= 3 && y + 1 <= 6)
					{
						NodeNumber = (x + 5) * 7 + y + 1;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				break;
			}
			case(3):
			{
				if ((x + 4) % 2 == 0)
				{
					if (x + 1 <= 3 && y - 1 >= 0)
					{
						NodeNumber = (x + 5) * 7 + y - 1;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x + 1 <= 3)
					{
						NodeNumber = (x + 5) * 7 + y;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				break;
			}
			case(4):
			{
				if (y - 1 >= 0)
				{
					NodeNumber = (x + 4) * 7 + y - 1;
					AdjancencyHexGridData[i].Emplace(NodeNumber);
				}
				break;
			}
			case(5):
			{
				if ((x + 4) % 2 == 0)
				{
					if (x - 1 >= -4 && y - 1 >= 0)
					{
						NodeNumber = (x + 3) * 7 + y - 1;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x - 1 >= -4)
					{
						NodeNumber = (x + 3) * 7 + y;
						AdjancencyHexGridData[i].Emplace(NodeNumber);
					}
				}
				break;
			}
			default:
			{
				UE_LOG(LogTemp, Warning, TEXT("GridMovementError"));
			}
			}
		}
		if (y == 6)
		{
			y = 0;
			++x;
		}
		else
		{
			++y;
		}
	}
}

void UAdjancencyHexGridData::InitDistanceData()
{
	TArray<TArray<int32>> Distance;
	Distance.SetNum(56);
	for (int32 i = 0; i < Distance.Num(); ++i)
	{
		Distance[i].SetNum(56);
	}

	for (int32 i = 0; i < Distance.Num(); ++i)
	{
		for (int32 j = 0; j < Distance[i].Num(); ++j)
		{
			i == j ? Distance[i][j] = 0 : Distance[i][j] = 10000;
		}
	}

	for (int32 i = 0; i < AdjancencyHexGridData.Num(); ++i)
	{
		for (int32 j = 0; j < AdjancencyHexGridData[i].Num(); ++j)
		{
			Distance[i][AdjancencyHexGridData[i][j]] = 1;
		}
	}

	for (int32 i = 0; i < Distance.Num(); ++i)
	{
		for (int32 j = 0; j < Distance.Num(); ++j)
		{
			for (int32 k = 0; k < Distance.Num(); ++k)
			{
				Distance[j][k] = std::min(Distance[j][k], Distance[j][i] + Distance[i][k]);
			}
		}
	}

	for (int32 i = 0; i < 56; ++i)
	{
		DistanceData.Emplace(i, Distance);
	}
}

int32 UAdjancencyHexGridData::GetDistanceAtoB(int32 LocationA, int32 LocationB)
{
	TArray<TArray<int32>> Distance = DistanceData[LocationA];
	return Distance[LocationA][LocationB];
}
