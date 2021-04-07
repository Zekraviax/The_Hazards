#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseClass_Widget_PauseMenu.generated.h"

// Forward Declarations
class AEntity_Player;
class UBaseClass_Widget_Options;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- References
	UPROPERTY()
	AEntity_Player* LocalPlayerReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<UBaseClass_Widget_Options> OptionsWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	UBaseClass_Widget_Options* OptionsWidget_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Options
	UFUNCTION(BlueprintCallable)
	void Function_ResumeGame();

	UFUNCTION(BlueprintCallable)
	void Function_QuitToMainMenu();

	UFUNCTION(BlueprintCallable)
	void Function_QuitToDesktop();

	UFUNCTION(BlueprintCallable)
	void OpenOptionsMenu();
};
