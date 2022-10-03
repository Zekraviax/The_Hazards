#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "EntityBaseCharacter.h"
#include "EntityPlayerCharacter.h"

#include "ActorComponentBaseStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEHAZARDS_API UActorComponentBaseStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorComponentBaseStats();

	// Function needed to replicate things in multiplayer
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Entity's maximum health points
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaximumHealthPoints = 100.f;

	// Entity's current health points
	// They die when it reaches zero
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentHealthPoints = 100.f;

	// Entity's maximum aura points
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	float MaximumAuraPoints = 100.f;

	// Entity's current aura points
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	float CurrentAuraPoints = 100.f;

	// Amount of time that must pass without losing health before it starts to regenerate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthRegenDelay = 5.f;

	// Amound of HP to regenerate per second
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthPointsRegenPerSecond = 1.f;

	// Amount of time that must pass without losing aura before it starts to regenerate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AuraRegenDelay = 5.f;

	// Amound of AP to regenerate per second
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AuraPointsRegenPerSecond = 1.f;

	// TimerHandle for AP regeneration
	FTimerHandle HealthPointsRegenTimerHandle;

	// TimerHandle for AP regeneration
	FTimerHandle AuraPointsRegenTimerHandle;

	// Player's level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Level = 1;

	// Player's current experience points
	// To-Do: Make NPCs give this much exp when killed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentExperiencePoints;

	// Money
	// NPCs should drop this amount when killed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Credits;

	// Used in weapon crafting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Scrap;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Add or subtract health points from this entity
	/**
	 * Handles subtracting aura points from this entity
	 * @param Points	Amount of aura points to add or subtract
	 */
	UFUNCTION()
	void UpdateCurrentHealthPoints(float Points);

	// Add or subtract aura points from this entity
	/**
	 * Handles subtracting aura points from this entity
	 * @param Points	Amount of aura points to add or subtract
	 */
	UFUNCTION()
	void UpdateCurrentAuraPoints(float Points);

	// Function used to regenerate entity's health points
	// Should be called only once per second
	// Used instead of renerating aura per tick in a Tick() function
	UFUNCTION()
	void HealthRegenIncrement();

	// Function used to regenerate entity's aura points
	// Should be called only once per second
	// Used instead of renerating aura per tick in a Tick() function
	UFUNCTION()
	void AuraRegenIncrement();

	// Return this entity's owner, cast as a EntityPlayerCharacter
	FORCEINLINE class AEntityPlayerCharacter* GetOwnerAsEntityPlayerCharacter() const { return Cast<AEntityPlayerCharacter>(GetOwner()); }

	/**
	 * Handles level-up related functions
	 * @param Increment		Number to add or subtract
	 */
	UFUNCTION()
	void UpdateLevel(int Increment);

	/**
	 * Add or subtract experience points from this entity
	 * @param Increment		Number to add or subtract
	 */
	UFUNCTION()
	void UpdateCurrentExperiencePoints(float Increment);

	/**
	 * Add or subtract money from this entity
	 * @param Increment		Number to add or subtract
	 */
	UFUNCTION()
	void UpdateCredits(int Increment);

	/**
	 * Add or subtract money from this entity
	 * @param Increment		Number to add or subtract
	 */
	UFUNCTION()
	void UpdateScrap(int Increment);
};