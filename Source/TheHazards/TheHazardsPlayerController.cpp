#include "TheHazardsPlayerController.h"


#include "ActorComponentBaseStats.h"
#include "EntityBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetHudBattle.h"
#include "WidgetMenuFindSessions.h"
#include "WidgetMenuHostSession.h"
#include "WidgetMenuMultiplayer.h"
#include "WidgetMenuPause.h"


void ATheHazardsPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess()  /  Pawn is possessed! Player Controller: %s"), *GetName());

	// Create the player's HUD
	if (WidgetHudBattleClass && !WidgetHudBattleReference) {
		WidgetHudBattleReference = CreateWidget<UWidgetHudBattle>(GetWorld(), WidgetHudBattleClass);

		// Set HUD variables for the first time
		WidgetHudBattleReference->UpdateHealthPointsInHud(Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->CurrentHealthPoints, Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->MaximumHealthPoints);
		WidgetHudBattleReference->UpdateAuraPointsInHud(Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->CurrentAuraPoints, Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->MaximumAuraPoints);

		WidgetHudBattleReference->AddToViewport();
		CurrentOpenWidgetClass = WidgetHudBattleClass;

		ValidWidgets.Add(WidgetHudBattleReference);
	}

	// Create the multiplayer menus
	if (WidgetMenuFindSessionsClass && !WidgetMenuFindSessionsReference) {
		WidgetMenuFindSessionsReference = CreateWidget<UWidgetMenuFindSessions>(GetWorld(), WidgetMenuFindSessionsClass);

		ValidWidgets.Add(WidgetMenuFindSessionsReference);
	}

	if (WidgetMenuMultiplayerClass && !WidgetMenuMultiplayerReference) {
		WidgetMenuMultiplayerReference = CreateWidget<UWidgetMenuMultiplayer>(GetWorld(), WidgetMenuMultiplayerClass);

		ValidWidgets.Add(WidgetMenuMultiplayerReference);
	}

	if (WidgetMenuHostSessionClass && !WidgetMenuHostSessionReference) {
		WidgetMenuHostSessionReference = CreateWidget<UWidgetMenuHostSession>(GetWorld(), WidgetMenuHostSessionClass);

		ValidWidgets.Add(WidgetMenuHostSessionReference);
	}

	// Create the in-game pause menu
	if (WidgetMenuPauseClass && !WidgetMenuPauseReference) {
		WidgetMenuPauseReference = CreateWidget<UWidgetMenuPause>(GetWorld(), WidgetMenuPauseClass);

		ValidWidgets.Add(WidgetMenuPauseReference);
	}
}


AEntityBaseCharacter* ATheHazardsPlayerController::GetPawnAsEntityBaseCharacter()
{
	return Cast<AEntityBaseCharacter>(GetPawn());
}


void ATheHazardsPlayerController::OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
	for (UUserWidget* Widget : ValidWidgets) {
		if (Widget->GetClass() == WidgetClass) {
			Widget->AddToViewport();
			CurrentOpenWidgetClass = WidgetClass;
		} else {
			Widget->RemoveFromViewport();
		}
	}

	// To-Do: Activate special functions based on which widget has been added to the viewport

	// Show or hide the cursor
	// Change input modes based on whether or not the current widget on-screen is the HUD
	if (WidgetClass == WidgetHudBattleClass) {
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());

		UGameplayStatics::SetGamePaused(GetWorld(), false);
	} else {
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	// Find Sessions
	if (WidgetClass == WidgetMenuFindSessionsClass) {
		WidgetMenuFindSessionsReference->BeginSearchForSessions();
	}
}