#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Engine/LevelStreaming.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

#include "TheHazards_GameInstance.generated.h"

// Forward Declarations
class AEntity_Player;
class USaveFile_Slot;
class USaveFile_MetaList;
class UBaseClass_Widget_LoadScreen;
class ATheHazards_GameInstance_TActor;

UCLASS()
class THE_HAZARDS_API UTheHazards_GameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_LoadScreen> LoadScreen_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_LoadScreen* LoadScreen_Widget;

// ------------------------- References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<AEntity_Player> Player_Entity_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* Player_Entity_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<ATheHazards_GameInstance_TActor> TickActor_Entity_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ATheHazards_GameInstance_TActor* TickActor_Entity_Reference;

// ------------------------- Save/Load
	UPROPERTY()
	USaveFile_MetaList* MetaListReference;

	UPROPERTY()
	USaveFile_Slot* SlotReference;

	UPROPERTY()
	FString SaveSlotName;

	UPROPERTY()
	FLatentActionInfo LatentActionInfo;

// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION()
	USaveFile_MetaList* ReturnMetaList();

	UFUNCTION(BlueprintCallable)
	void LoadSaveFile(FString SaveFileSlotName);

	UFUNCTION(BlueprintCallable)
	void LoadSaveFilePartTwo();

	UFUNCTION(BlueprintCallable)
	void LoadSaveFilePartThree();

	UFUNCTION(BlueprintCallable)
	void LoadSaveFilePartFour();
};