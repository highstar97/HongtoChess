#pragma once

#include "GameFramework/Actor.h"
#include "MapMaker.generated.h"

class ATile;
/*
	Before Upgrade for 8 player, we make game for 2 player
	So now, This code is for 2 Player ( JustForTwoPlayer()... )
	If you want to change game for 8 player, Delete Some Function and Change BeginPlay()
*/
UCLASS()
class HONGTOCHESS_API AMapMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapMaker();

protected:
	virtual void BeginPlay() override;

	void MakeCircleGrid();
	void MakeHexGrid(int32 OriginIndex);
	void MakeChampionLocker(int32 OriginIndex);
	void MakeItemLocker(int32 OriginIndex);
	void MakeInterestIndicator(int32 OriginIndex);

	void JustForTwoPlayer();

protected:
	TArray<FIntPoint> OriginArray;

	TArray<TArray<ATile*>> HexGrid2DArray;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 GridWidth;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 GridHeight;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float OddRowHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<ATile> HexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<ATile> HalfSquareTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<ATile> SquareTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<ATile> CircleTile;
};