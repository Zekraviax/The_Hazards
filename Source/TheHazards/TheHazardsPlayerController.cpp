#include "TheHazardsPlayerController.h"


#include "ActorComponentBaseStats.h"
#include "Blueprint/UserWidget.h"
#include "EntityBaseCharacter.h"
#include "EntityPlayerCharacter.h"


void ATheHazardsPlayerController::OnMouseButtonUpOnWidget()
{
	if (CurrentDraggingWidget) {
		CurrentDraggingWidget->RemoveFromParent();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("ATheHazardsPlayerController / OnMouseButtonUpOnWidget() / Error: CurrentDraggingWidget reference is not valid."));
	}
}


AEntityPlayerCharacter* ATheHazardsPlayerController::GetPawnAsEntityPlayerCharacter()
{
	return Cast<AEntityPlayerCharacter>(GetPawn());
}