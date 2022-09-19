#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityBaseCharacter.h"
#include "ActorComponentBaseStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEHAZARDS_API UActorComponentBaseStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorComponentBaseStats();

	// Entity's maximum health points
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumHealthPoints = 100.f;

	// Entity's current health points
	// They die when it reaches zero
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealthPoints = 100.f;

	// Entity's maximum aura points
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumAuraPoints = 100.f;

	// Entity's current aura points
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentAuraPoints = 100.f;

	// Amount of time that must pass without losing aura before it starts to regenerate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AuraRegenDelay = 5.f;

	// Amound of AP to regenerate per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AuraPointsRegenPerSecond = 1.f;

	// TimerHandle for AP regeneration
	FTimerHandle AuraPointsRegenTimerHandle;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
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

	// Function used to regenerate entity's aura
	// Should be called only once per second
	// Used instead of renerating aura per tick in a Tick() function
	UFUNCTION()
	void AuraRegenIncrement();

	// Return this entity's owner, cast as a EntityBaseCharacter
	FORCEINLINE class AEntityBaseCharacter* GetOwnerAsEntityBaseCharacter() const { return Cast<AEntityBaseCharacter>(GetOwner()); }
};
