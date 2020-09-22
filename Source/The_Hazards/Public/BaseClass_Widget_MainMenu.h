#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseClass_Widget_SaveLoad.h"
#include "BaseClass_Widget_Options.h"
#include "BaseClass_Widget_LoadScreen.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

#include "BaseClass_Widget_MainMenu.generated.h"

// Forward Declarations
class AEntity_Player;
class AEntity_Player_MainMenu;
class ATheHazards_PlayerState;
class ABaseClass_PlayerController;
class ABaseClass_MainMenuController;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_Options> Options_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_LoadScreen> LoadScreen_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UBaseClass_Widget_LoadScreen* LoadScreen_Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentOpenMenuWidget;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player_MainMenu* PlayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ABaseClass_PlayerController* Player_Controller_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<AEntity_Player> Player_Entity_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AEntity_Player* Player_Entity_Reference;

// ------------------------- Technical Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	TSubclassOf<ABaseClass_PlayerController> PlayerController_Standard_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	TSubclassOf<ABaseClass_MainMenuController> PlayerController_MainMenu_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Menus
public:
	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void NewGame();

	UFUNCTION(BlueprintCallable)
	void ClearLoadingScreen();

	UFUNCTION(BlueprintCallable)
	void OpenLoadGameMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOptionsMenu();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	//UFUNCTION(BlueprintCallable)
	//void OpenSaveLoadMenu(bool SaveMode);
};
