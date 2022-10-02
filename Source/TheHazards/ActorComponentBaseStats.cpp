#include "ActorComponentBaseStats.h"


#include "WidgetHudBattle.h"


// Sets default values for this component's properties
UActorComponentBaseStats::UActorComponentBaseStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UActorComponentBaseStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Each property of the component that is replicated needs to be specified here
	DOREPLIFETIME(UActorComponentBaseStats, MaximumAuraPoints);
	DOREPLIFETIME(UActorComponentBaseStats, CurrentAuraPoints);
}


// Called when the game starts
void UActorComponentBaseStats::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UActorComponentBaseStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	if (GetOwnerAsEntityPlayerCharacter()) {
		GetOwnerAsEntityPlayerCharacter()->WidgetHudBattleReference->UpdateHealthPointsInHud(CurrentHealthPoints, MaximumHealthPoints);
	}

	// If the entity lost HP, start the regen timer
	// If there are any timers already underway, cancel them
	if (Points < 0.f) {
		//GetWorld()->GetTimerManager().ClearTimer(HealthPointsRegenTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(HealthPointsRegenTimerHandle, this, &UActorComponentBaseStats::HealthRegenIncrement, HealthRegenDelay, false);
	}
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
	if (GetOwnerAsEntityPlayerCharacter()) {
		GetOwnerAsEntityPlayerCharacter()->WidgetHudBattleReference->UpdateAuraPointsInHud(CurrentAuraPoints, MaximumAuraPoints);
	}

	// If the entity lost AP, start the regen timer
	// If there are any timers already underway, cancel them
	if (Points < 0.f) {
		GetWorld()->GetTimerManager().SetTimer(AuraPointsRegenTimerHandle, this, &UActorComponentBaseStats::AuraRegenIncrement, AuraRegenDelay, false);
	}
}


void UActorComponentBaseStats::HealthRegenIncrement()
{
	UpdateCurrentHealthPoints(HealthPointsRegenPerSecond);

	GetWorld()->GetTimerManager().SetTimer(HealthPointsRegenTimerHandle, this, &UActorComponentBaseStats::HealthRegenIncrement, 1.f, false);
}


void UActorComponentBaseStats::AuraRegenIncrement()
{
	UpdateCurrentAuraPoints(AuraPointsRegenPerSecond);

	GetWorld()->GetTimerManager().SetTimer(AuraPointsRegenTimerHandle, this, &UActorComponentBaseStats::AuraRegenIncrement, 1.f, false);
}


void UActorComponentBaseStats::UpdateLevel(int Increment)
{
	Level += Increment;

	// Update player's hud
	if (GetOwnerAsEntityPlayerCharacter()) {
		GetOwnerAsEntityPlayerCharacter()->WidgetHudBattleReference->UpdateLevelInHud(Level);
	}
}


void UActorComponentBaseStats::UpdateCurrentExperiencePoints(float Increment)
{
	CurrentExperiencePoints += Increment;

	// Level up the player if they reach the exp threshold
	if (CurrentExperiencePoints >= (Level * 100)) {
		CurrentExperiencePoints -= (Level * 100);

		UpdateLevel(1);
	}

	// Update player's hud
	if (GetOwnerAsEntityPlayerCharacter()) {
		GetOwnerAsEntityPlayerCharacter()->WidgetHudBattleReference->UpdateExperiencePointsInHud(CurrentExperiencePoints);
	}
}