#include "../Map/MapMaker.h"
#include "../Map/Tile.h"
#include "GenericPlatform/GenericPlatformMath.h"

AMapMaker::AMapMaker()
{
	int32 distance = 3000;

	for (int32 i = 0; i < 3; ++i)
	{
		for (int32 j = 0; j < 3; ++j)
		{
			if (i == 1 && j == 1)	continue;
			OriginArray.Emplace(FIntPoint(((i - 1) * distance), ((j - 1) * distance)));
		}
	}
}

void AMapMaker::MakeCircleGrid()
{
	ATile* NewTile = GetWorld()->SpawnActor<ATile>(CircleTile, FVector(0, 0, 0), FRotator::ZeroRotator);
	NewTile->SetActorScale3D(FVector(20.0f,20.0f,2.0f));
}

void AMapMaker::BeginPlay()
{
	Super::BeginPlay();
	MakeCircleGrid();

	for (int32 i = 0; i < OriginArray.Num(); ++i)
	{
		MakeHexGrid(i);
		MakeChampionLocker(i);
		MakeItemLocker(i);
		MakeInterestIndicator(i);
	}
}

void AMapMaker::MakeHexGrid(int32 OriginIndex)
{
	FVector Origin = FVector(OriginArray[OriginIndex]);
	FVector Adjusted = Origin + FVector(500, -300 * sqrt(3), 0);

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

			ATile* NewTile = GetWorld()->SpawnActor<ATile>(HexTile, Adjusted + FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);
			NewTile->TileIndex = FIntPoint(x-4, y);
			NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x - 4, y));
			HexGrid2DArray[x][y] = NewTile;
		}
	}
}

void AMapMaker::MakeChampionLocker(int32 OriginIndex)
{
	const float SquareVerticalOffset = 20.0f;

	FVector Origin = FVector(OriginArray[OriginIndex]);
	FVector Adjusted = Origin + FVector(700, 500, 0);

	for (int32 y = 0; y < 10; ++y)
	{
		const float yPos = -y * (100 + SquareVerticalOffset);
		
		ATile* NewTile = GetWorld()->SpawnActor<ATile>(HalfSquareTile, Adjusted + FVector(FIntPoint(0, yPos)), FRotator::ZeroRotator);
		NewTile->TileIndex = FIntPoint(-1, y);
		NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, -1, y));
	}

	Adjusted = Origin + FVector(-800, -550, 0);

	for (int32 y = 0; y < 10; ++y)
	{
		const float yPos = y * (100 + SquareVerticalOffset);

		ATile* NewTile = GetWorld()->SpawnActor<ATile>(HalfSquareTile, Adjusted + FVector(FIntPoint(0, yPos)), FRotator::ZeroRotator);
		NewTile->TileIndex = FIntPoint(0, y);
		NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, 0, y));
	}
}

void AMapMaker::MakeItemLocker(int32 OriginIndex)
{
	FVector Origin = FVector(OriginArray[OriginIndex]);
	FVector Adjusted = Origin + FVector(650, 710, 0);

	for (int32 x = 0; x < 2; ++x)
	{
		const float xPos = -x * 100;

		ATile* NewTile = GetWorld()->SpawnActor<ATile>(SquareTile, Adjusted + FVector(FIntPoint(xPos, 0)), FRotator::ZeroRotator);
		NewTile->TileIndex = FIntPoint(0, x);
		NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, 0, x));
	}

	Adjusted = Origin + FVector(-750, -760, 0);

	for (int32 x = 0; x < 2; ++x)
	{
		const float xPos = x * 100;

		ATile* NewTile = GetWorld()->SpawnActor<ATile>(SquareTile, Adjusted + FVector(FIntPoint(xPos, 0)), FRotator::ZeroRotator);
		NewTile->TileIndex = FIntPoint(0, x);
		NewTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, 0, x));
	}
}

void AMapMaker::MakeInterestIndicator(int32 OriginIndex)
{
	FVector Origin = FVector(OriginArray[OriginIndex]);
	FVector Adjusted = Origin + FVector(350, 760, 0);

	for (int32 x = 0; x < 5; ++x)
	{
		const float xPos = -x * 100;

		ATile* NewBaseTile = GetWorld()->SpawnActor<ATile>(HalfSquareTile, Adjusted + FVector(FIntPoint(xPos, 0)), FRotator::ZeroRotator);
		ATile* NewInterestTile = GetWorld()->SpawnActor<ATile>(CircleTile, Adjusted + FVector(xPos, 0, 80), FRotator(-50, -90, 0));

		NewBaseTile->TileIndex = FIntPoint(x, -1);
		NewInterestTile->TileIndex = FIntPoint(x, -1);
		NewBaseTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, -1));
		NewInterestTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, -1));
	}

	Adjusted = Origin + FVector(-450, -810, 0);

	for (int32 x = 0; x < 5; ++x)
	{
		const float xPos = x * 100;

		ATile* NewBaseTile = GetWorld()->SpawnActor<ATile>(HalfSquareTile, Adjusted + FVector(FIntPoint(xPos, 0)), FRotator::ZeroRotator);
		ATile* NewInterestTile = GetWorld()->SpawnActor<ATile>(CircleTile, Adjusted + FVector(xPos, 0, 80), FRotator(50, -90, 0));

		NewBaseTile->TileIndex = FIntPoint(x, 0);
		NewInterestTile->TileIndex = FIntPoint(x, 0);
		NewBaseTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, 0));
		NewInterestTile->SetActorLabel(FString::Printf(TEXT("PC%d's\n(%d,%d)"), OriginIndex, x, 0));
	}
}