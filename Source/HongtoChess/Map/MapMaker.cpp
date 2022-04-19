#include "../Map/MapMaker.h"
#include "../Map/Tile.h"
#include "GenericPlatform/GenericPlatformMath.h"

AMapMaker::AMapMaker()
{
	int32 distance = 4300;

	for (int32 i = 0; i < 3; ++i)
	{
		for (int32 j = 0; j < 3; ++j)
		{
			if (i == 1 && j == 1)	continue;
			OriginArray.Emplace(FIntPoint(((i - 1) * distance) + 500, ((j - 1) * distance)) - 650 + 50*sqrt(3));
		}
	}
}

void AMapMaker::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < OriginArray.Num(); ++i)
	{
		MakeHexGrid(i);
		MakeChampionLocker(i);
		MakeInterestIndicator(i);
	}
}

void AMapMaker::MakeHexGrid(int32 OriginIndex)
{
	FVector Origin = FVector(OriginArray[OriginIndex]);

	HexGrid2DArray.SetNumZeroed(GridHeight);
	for (int32 i = 0; i < HexGrid2DArray.Num(); ++i)
	{
		HexGrid2DArray[i].SetNumZeroed(GridWidth);
	}

	for (int32 x = 0; x < GridHeight; ++x)
	{
		for (int32 y = 0; y < GridWidth; ++y)
		{
			const bool oddRow = x % 2 == 1;
			const float yPos = oddRow ? y * TileHorizontalOffset : (y * TileHorizontalOffset) - OddRowHorizontalOffset;
			const float xPos = -x * TileVerticalOffset;

			ATile* NewTile = GetWorld()->SpawnActor<ATile>(HexTile, Origin + FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);
			NewTile->TileIndex = FIntPoint(x-4, y);
			NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x - 4, y));
			HexGrid2DArray[x][y] = NewTile;
		}
	}
}

void AMapMaker::MakeChampionLocker(int32 OriginIndex)
{
	FVector Origin = FVector(OriginArray[OriginIndex]);
	FVector Adjusted = Origin + FVector(-1300, +605 - 50 * sqrt(3) - 500 * sqrt(2), 0);

	for (int32 y = 0; y < 10; ++y)
	{
		const float SquareVerticalOffset = 10.0f;
		const float yPos = y * (100 * sqrt(2) + SquareVerticalOffset);
		
		ATile* NewTile = GetWorld()->SpawnActor<ATile>(SquareTile, Adjusted + FVector(FIntPoint(0, yPos)), FRotator::ZeroRotator);
		NewTile->TileIndex = FIntPoint(0, y);
		NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, 0, y));
	}

	Adjusted = Origin + FVector(+200, 695 - 50 * sqrt(3) + 400 * sqrt(2), 0);

	for (int32 y = 0; y < 10; ++y)
	{
		const float SquareVerticalOffset = 10.0f;
		const float yPos = -y * (100 * sqrt(2) + SquareVerticalOffset);

		ATile* NewTile = GetWorld()->SpawnActor<ATile>(SquareTile, Adjusted + FVector(FIntPoint(0, yPos)), FRotator::ZeroRotator);
		NewTile->TileIndex = FIntPoint(-1, y);
		NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, -1, y));
	}
}

void AMapMaker::MakeInterestIndicator(int32 OriginIndex)
{
	FVector Origin = FVector(OriginArray[OriginIndex]);
	
	// ¹Ù´Ú »ý¼º
	FVector Adjusted = Origin + FVector(-500, -300, 0);
	for (int32 x = 0; x < 5; ++x)
	{
		const float xPos = -x * 100 * sqrt(2);

		ATile* NewBaseTile = GetWorld()->SpawnActor<ATile>(SquareTile, Adjusted + FVector(FIntPoint(xPos, 0)), FRotator::ZeroRotator);
		ATile* NewInterestIndicator = GetWorld()->SpawnActor<ATile>(CircleTile, Adjusted + FVector(xPos, 0, 50), FRotator::ZeroRotator);

		NewBaseTile->TileIndex = FIntPoint(x, 0);
		NewInterestIndicator->TileIndex = FIntPoint(x, 0);
		NewBaseTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, 0));
		NewInterestIndicator->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, 0));
	}

	Adjusted = Origin + FVector(-600, 1300, 0);

	for (int32 x = 0; x < 5; ++x)
	{
		const float xPos = x * 100 * sqrt(2);

		ATile* NewBaseTile = GetWorld()->SpawnActor<ATile>(SquareTile, Adjusted + FVector(FIntPoint(xPos, 0)), FRotator::ZeroRotator);
		ATile* NewInterestIndicator = GetWorld()->SpawnActor<ATile>(CircleTile, Adjusted + FVector(xPos, 0, 50), FRotator::ZeroRotator);

		NewBaseTile->TileIndex = FIntPoint(x, 1);
		NewInterestIndicator->TileIndex = FIntPoint(x, 1);
		NewBaseTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, 1));
		NewInterestIndicator->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, 1));
	}
}