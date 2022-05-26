#include "HCGameMode.h"
#include "HCGameState.h"
#include "HCPlayerState.h"
#include "HCPlayerCharacter.h"
#include "HCPlayerController.h"
#include "HCThirdPartySocketServerActor.h"
#include "Map/AdjancencyHexGridData.h"

AHCGameMode::AHCGameMode()
{
	DefaultPawnClass = AHCPlayerCharacter::StaticClass();
	PlayerControllerClass = AHCPlayerController::StaticClass();
	PlayerStateClass = AHCPlayerState::StaticClass();
	GameStateClass = AHCGameState::StaticClass();

	BigRound = 1;
	SmallRound = 1;
}

void AHCGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//TPSocket = (AHCThirdPartySocketServer*)GetWorld()->SpawnActor(AHCThirdPartySocketServer::StaticClass());
	AdjancencyHexGridData = NewObject<UAdjancencyHexGridData>();
}

// Round Play
// Check Round Finish
// Next Round