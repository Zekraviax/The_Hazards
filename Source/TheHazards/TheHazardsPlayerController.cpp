#include "TheHazardsPlayerController.h"


#include "ActorComponentBaseStats.h"
#include "EntityBaseCharacter.h"


AEntityBaseCharacter* ATheHazardsPlayerController::GetPawnAsEntityBaseCharacter()
{
	return Cast<AEntityBaseCharacter>(GetPawn());
}