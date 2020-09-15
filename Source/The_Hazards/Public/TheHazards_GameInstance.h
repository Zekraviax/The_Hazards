#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Engine/LevelStreaming.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

#include "TheHazards_GameInstance.generated.h"

// Forward Declarations
class USaveFile_Slot;
class UBaseClass_Widget_LoadScreen;

UCLASS()
class THE_HAZARDS_API UTheHazards_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_LoadScreen> LoadScreen_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_LoadScreen* LoadScreen_Widget;

// ------------------------- Save/Load


// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION()
	void LoadSaveFile(USaveFile_Slot* SlotReference);
};