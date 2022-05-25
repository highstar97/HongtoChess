#include "HCGameMode.h"
#include "HCPlayerController.h"
#include "HCThirdPartySocketServerActor.h"

AHCGameMode::AHCGameMode()
{
	PlayerControllerClass = AHCPlayerController::StaticClass();

	//TPSocket = (AHCThirdPartySocketServer*)GetWorld()->SpawnActor(AHCThirdPartySocketServer::StaticClass());

	BigRound = 1;
	SmallRound = 1;
}

void AHCGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

// Round Play
// Check Round Finish
// Next Round