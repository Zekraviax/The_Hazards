#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Subtract aura points from this entity
	/**
	 * Handles subtracting aura points from this entity
	 * @param Points	Amount of aura points to subtract
	 */
	UFUNCTION()
	void ChangeCurrentAuraPoints(float Points);
};
