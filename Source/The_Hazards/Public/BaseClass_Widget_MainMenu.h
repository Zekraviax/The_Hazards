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
class ABaseClass_PlayerController;
class ABaseClass_MainMenuController;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_MainMenu : public UUserWidget
{
	GENERATED_BODY()

	UBaseClass_Widget_MainMenu(const FObjectInitializer& ObjectInitializer);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentOpenMenuWidget;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player_MainMenu* PlayerReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UClass* Player_Entity_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* Player_Entity_Reference;

// ------------------------- Technical Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	TSubclassOf<ABaseClass_PlayerController> PlayerController_Standard_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	TSubclassOf<ABaseClass_MainMenuController> PlayerController_MainMenu_Reference;

// Functions
// --------------------------------------------------
	//virtual ~UBaseClass_Widget_MainMenu();
//private:
//	UBaseClass_Widget_MainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer);

// ------------------------- Menus
public:
	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void NewGame(TSubclassOf<AEntity_Player> EntityPlayerBlueprintClass);

	UFUNCTION(BlueprintCallable)
	void OpenLoadGameMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOptionsMenu();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	//UFUNCTION(BlueprintCallable)
	//void OpenSaveLoadMenu(bool SaveMode);
};
