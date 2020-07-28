#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseClass_Widget_SaveLoad.h"
#include "Kismet/GameplayStatics.h"

#include "BaseClass_Widget_MainMenu.generated.h"


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_SaveLoad> SaveLoad_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentOpenMenuWidget;

// Functions
// --------------------------------------------------

// ------------------------- Menus
	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void NewGame();

	UFUNCTION(BlueprintCallable)
	void OpenLoadGameMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOptionsMenu();

	UFUNCTION(BlueprintCallable)
	void QuitGame();
};
