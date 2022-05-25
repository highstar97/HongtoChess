#include "HCPlayerController.h"
#include "HCGameMode.h"
#include "HCThirdPartySocketServerActor.h"

void AHCPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AHCPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AHCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Test"), EInputEvent::IE_Pressed, this, &AHCPlayerController::Test);
}

void AHCPlayerController::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Shift S is Pressed"));

	auto HCGameMode = Cast<AHCGameMode>(GetWorld()->GetAuthGameMode());
	HCGameMode->GetTPSocket()->Test();
}