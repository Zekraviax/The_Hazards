#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheHazardsGameMode.generated.h"


class AEntityPlayerCharacter;
class ATheHazardsPlayerController;


UCLASS(minimalapi)
class ATheHazardsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Keep a reference to the player character blueprint for comparison
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEntityPlayerCharacter> PlayerCharacterBlueprintClass;

	// Constructor
	ATheHazardsGameMode();

	// Handle a player joining a session
	// Destroy and spawned pawns and have the player possess a pre-existing pawn ?
	UFUNCTION(BlueprintCallable)
	virtual void PostLogin(APlayerController* NewPlayerController) override;
};