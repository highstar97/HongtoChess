#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UStaticMeshComponent;
// class UChampion;

UCLASS()
class HONGTOCHESS_API ATile : public AActor
{
	GENERATED_BODY()

public:
	ATile();

public:
	UPROPERTY(VisibleInstanceOnly, Category = "Tile")
	FIntPoint TileIndex;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Tile")
	UStaticMeshComponent* TileMesh;

	// 필요 없을지도?
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Champion")
	//UChampion* Champion = nullptr;
};
