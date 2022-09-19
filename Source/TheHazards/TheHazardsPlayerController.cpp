#include "TheHazardsPlayerController.h"


#include "ActorComponentBaseStats.h"
#include "EntityBaseCharacter.h"
#include "WidgetHudBattle.h"



void ATheHazardsPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess()  /  Pawn is possessed!"));

	// To-Do: Only open widgets when possessed by a player controller
	if (WidgetHudBattleClass && !WidgetHudBattleReference) {
		WidgetHudBattleReference = CreateWidget<UWidgetHudBattle>(GetWorld(), WidgetHudBattleClass);

		// To-Do: Add a ControllingEntity to the Battle HUD ?
		//WidgetHudBattleReference->SetOwningLocalPlayer = GetController();

		// Set HUD variables for the first time
		WidgetHudBattleReference->UpdateHealthPointsInHud(Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->CurrentHealthPoints, Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->MaximumHealthPoints);
		WidgetHudBattleReference->UpdateAuraPointsInHud(Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->CurrentAuraPoints, Cast<AEntityBaseCharacter>(GetPawn())->GetBaseStatsComponent()->MaximumAuraPoints);

		WidgetHudBattleReference->AddToViewport();
	}
}