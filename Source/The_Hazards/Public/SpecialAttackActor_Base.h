#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecialAttackActor_Base.generated.h"

// Forward Declarations
class AFunctionLibrary_SpecialAttacks;
class AEntity_Base;


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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	AEntity_Base* AttackingEntity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	AFunctionLibrary_SpecialAttacks* SpecialAttackLibrary_Reference;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TArray<AEntity_Base*> AttackedEntitiesArray;

// Functions
// --------------------------------------------------
	// Return attack style and/or animations
};