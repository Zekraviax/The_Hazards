#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecialAttackActor_Base.generated.h"

// Forward Declarations
class AFunctionLibrary_SpecialAttacks;


UCLASS()
class THE_HAZARDS_API ASpecialAttackActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecialAttackActor_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Owner
	UPROPERTY()
	AEntity_Base* AttackingEntity;

	UPROPERTY()
	AFunctionLibrary_SpecialAttacks* SpecialAttackLibrary_Reference;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TArray<AEntity_Base*> AttackedEntitiesArray;
};