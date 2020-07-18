#pragma once

#include "CoreMinimal.h"
#include "Entity_Base.h"
#include "Entity_Destructible.generated.h"


UCLASS()
class THE_HAZARDS_API AEntity_Destructible : public AEntity_Base
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
// Base Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	AEntity_Destructible();
};
