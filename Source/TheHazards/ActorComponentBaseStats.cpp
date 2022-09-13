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


void UActorComponentBaseStats::UpdateCurrentHealthPoints(float Points)
{
	// Prevent the players' current HP fro exceeding their maximum HP
	if (CurrentHealthPoints + Points > MaximumHealthPoints) {
		CurrentHealthPoints = MaximumHealthPoints;
	} else {
		CurrentHealthPoints += Points;
	}

	// Update player's hud
	Cast<AEntityBaseCharacter>(GetOwner())->WidgetHudBattleReference->UpdateHealthPointsInHud(CurrentHealthPoints, MaximumAuraPoints);
}


void UActorComponentBaseStats::UpdateCurrentAuraPoints(float Points)
{
	// Prevent the players' current AP fro exceeding their maximum AP
	if (CurrentAuraPoints + Points > MaximumAuraPoints) {
		CurrentAuraPoints = MaximumAuraPoints;
	} else {
		CurrentAuraPoints += Points;
	}

	// Update player's hud
	Cast<AEntityBaseCharacter>(GetOwner())->WidgetHudBattleReference->UpdateAuraPointsInHud(CurrentAuraPoints, MaximumAuraPoints);

	// If the entity lost AP, start the regen timer
	// If there are any timers already underway, cancel them
	if (Points < 0.f) {
		GetWorld()->GetTimerManager().ClearTimer(AuraPointsRegenTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(AuraPointsRegenTimerHandle, this, &UActorComponentBaseStats::AuraRegenIncrement, AuraRegenDelay, false);
	}
}


void UActorComponentBaseStats::AuraRegenIncrement()
{
	UpdateCurrentAuraPoints(AuraPointsRegenPerSecond);

	GetWorld()->GetTimerManager().SetTimer(AuraPointsRegenTimerHandle, this, &UActorComponentBaseStats::AuraRegenIncrement, 1.f, false);
}