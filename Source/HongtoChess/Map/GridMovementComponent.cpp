#include "Map/GridMovementComponent.h"

UGridMovementComponent::UGridMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	int32 x = -4;
	int32 y = 0;
	GridGraphData.SetNum(56);
	for (int32 i = 0; i < GridGraphData.Num(); ++i)
	{
		GridGraphData[i].Empty();

		int32 NodeNumber ;
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
						GridGraphData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x - 1 >= -4 && y + 1 <= 6)
					{
						NodeNumber = (x + 3) * 7 + y + 1;
						GridGraphData[i].Emplace(NodeNumber);
					}
				}
				break;
			}
			case(1):
			{
				if (y + 1 <= 6)
				{
					NodeNumber = (x + 4) * 7 + y + 1;
					GridGraphData[i].Emplace(NodeNumber);
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
						GridGraphData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x + 1 <= 3 && y + 1 <= 6)
					{
						NodeNumber = (x + 5) * 7 + y + 1;
						GridGraphData[i].Emplace(NodeNumber);
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
						GridGraphData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x + 1 <= 3)
					{
						NodeNumber = (x + 5) * 7 + y;
						GridGraphData[i].Emplace(NodeNumber);
					}
				}
				break;
			}
			case(4):
			{
				if (y - 1 >= 0)
				{
					NodeNumber = (x + 4) * 7 + y - 1;
					GridGraphData[i].Emplace(NodeNumber);
				}
				break;
			}
			case(5):
			{
				if ((x + 4) % 2 == 0)
				{
					if (x - 1 >= -4 && y -1 >= 0)
					{
						NodeNumber = (x + 3) * 7 + y - 1;
						GridGraphData[i].Emplace(NodeNumber);
					}
				}
				else
				{
					if (x - 1 >= -4)
					{
						NodeNumber = (x + 3) * 7 + y;
						GridGraphData[i].Emplace(NodeNumber);
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

void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGridMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}