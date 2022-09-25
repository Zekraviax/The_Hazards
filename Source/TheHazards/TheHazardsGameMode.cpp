// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheHazardsGameMode.h"

#include "EntityPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TheHazardsHUD.h"
#include "TheHazardsPlayerController.h"

#include "UObject/ConstructorHelpers.h"


ATheHazardsGameMode::ATheHazardsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/EntityBaseCharacterBP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATheHazardsHUD::StaticClass();
}


void ATheHazardsGameMode::PostLogin(APlayerController* NewPlayerController)
{
	UE_LOG(LogTemp, Warning, TEXT("OnPlayerPostLogin() / Player Controller %s has logged in"), *NewPlayerController->GetName());

	// Cast to our player controller
	ATheHazardsPlayerController* NewHazardsPlayerController = Cast<ATheHazardsPlayerController>(NewPlayerController);

	// Find any pre-existing player characters and assign the player controller to one
	TArray<AActor*> FoundPlayerCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntityPlayerCharacter::StaticClass(), FoundPlayerCharacters);

	// Destroy any spawned actors
	// Unless the actor was pre-existing
	if (NewPlayerController->GetPawn()) {
		if (NewPlayerController->GetPawn()->GetClass() != PlayerCharacterBlueprintClass) {
			NewPlayerController->GetPawn()->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("OnPlayerPostLogin() / Player's pawn has been destroyed"));
		} else {
			UE_LOG(LogTemp, Warning, TEXT("OnPlayerPostLogin() / Player's pawn is a pre-existing character"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("OnPlayerPostLogin() / Player's pawn is not valid"));
	}

	if (!NewPlayerController->GetPawn()) {
		for (AActor* Actor : FoundPlayerCharacters) {
			AEntityPlayerCharacter* Character = Cast<AEntityPlayerCharacter>(Actor);

			// Only assign a character to a controller if the character doesn't already have a controller
			if (!Character->GetController()) {
				UE_LOG(LogTemp, Warning, TEXT("OnPlayerPostLogin() / Found character for player to possess"));

				NewPlayerController->Possess(Character);
				Character->SetOwner(NewPlayerController);

				break;
			}
		}
	}

	// Tell the player character to create widgets and add the HUD to their viewport
	Cast<AEntityPlayerCharacter>(NewPlayerController->GetPawn())->ClientCreateWidgets();

	// To-Do: Set player controller's input mode to GameOnly and make sure their game is unpaused
	// Lock mouse to window as well (?)
	NewPlayerController->SetInputMode(FInputModeGameOnly());
}