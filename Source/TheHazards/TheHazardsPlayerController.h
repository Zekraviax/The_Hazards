#pragma once


#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "TheHazardsPlayerController.generated.h"


class AEntityPlayerCharacter;


UCLASS()
class THEHAZARDS_API ATheHazardsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* CurrentDraggingWidget;

	UFUNCTION(BlueprintCallable)
	void OnMouseButtonUpOnWidget();

	UFUNCTION()
	AEntityPlayerCharacter* GetPawnAsEntityPlayerCharacter();

	// Return this controller's pawn, cast as an EntityBaseCharacter
	FORCEINLINE class AEntityBaseCharacter* GetPawnAsEntityBaseCharacter() const { return Cast<AEntityBaseCharacter>(GetPawn()); }
};