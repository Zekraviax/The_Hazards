#pragma once

#include "CoreMinimal.h"
#include "SpecialAttackActor_Base.h"

#include "SpecialAttackActor_Assassinate.generated.h"

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API ASpecialAttackActor_Assassinate : public ASpecialAttackActor_Base
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnEntityOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
