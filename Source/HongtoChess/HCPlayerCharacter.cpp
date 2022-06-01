#include "HCPlayerCharacter.h"
#include "HCGameMode.h"
#include "HCThirdPartySocketServerActor.h"

AHCPlayerCharacter::AHCPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AHCPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AHCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Test"), EInputEvent::IE_Pressed, this, &AHCPlayerCharacter::Test); // Need to Fix
}

void AHCPlayerCharacter::Test() 
{
	UE_LOG(LogTemp, Warning, TEXT("Shift S is Pressed"));

	auto HCGameMode = Cast<AHCGameMode>(GetWorld()->GetAuthGameMode());
	//HCGameMode->GetTPSocket()->Test();
}