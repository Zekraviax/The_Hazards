#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheHazardsPlayerController.generated.h"


class UWidgetHudBattle;


UCLASS()
class THEHAZARDS_API ATheHazardsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Used to add the widget to the players' screen whenever their character is spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetHudBattle> WidgetHudBattleClass;

	// Keep a reference to the widget itself so we can show and hide it instead of creating and destroying it every time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetHudBattle* WidgetHudBattleReference;

	// Use this function to create widgets for the first and only time
	virtual void OnPossess(APawn* InPawn) override;

	// Return this controller's pawn, cast as a EntityBaseCharacter
	//FORCEINLINE class AEntityBaseCharacter* GetPawnAsEntityBaseCharacter() const { return Cast<AEntityBaseCharacter>(GetPawn()); }
};