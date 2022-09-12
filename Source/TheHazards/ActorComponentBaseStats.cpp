#include "ActorComponentBaseStats.h"


#include "EntityBaseCharacter.h"
#include "WidgetHudBattle.h"


// Sets default values for this component's properties
UActorComponentBaseStats::UActorComponentBaseStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorComponentBaseStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorComponentBaseStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UActorComponentBaseStats::ChangeCurrentAuraPoints(float Points)
{
	// Prevent the players' current AP fro exceeding their maximum AP
	if (CurrentAuraPoints + Points > MaximumAuraPoints) {
		CurrentAuraPoints = MaximumAuraPoints;
	} else {
		CurrentAuraPoints += Points;
	}


	// Update player's hud
	Cast<AEntityBaseCharacter>(GetOwner())->WidgetHudBattleReference->UpdateAuraPointsText(CurrentAuraPoints, MaximumAuraPoints);
}