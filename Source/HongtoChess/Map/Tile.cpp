#include "../Map/Tile.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>

ATile::ATile()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
    TileMesh->SetupAttachment(RootComponent);
}