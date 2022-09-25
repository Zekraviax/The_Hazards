#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheHazardsPlayerController.generated.h"


class AEntityBaseCharacter;


UCLASS()
class THEHAZARDS_API ATheHazardsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Return this controller's pawn, cast as an EntityBaseCharacter
	AEntityBaseCharacter* GetPawnAsEntityBaseCharacter();
};