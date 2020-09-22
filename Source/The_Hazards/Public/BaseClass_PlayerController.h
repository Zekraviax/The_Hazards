#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SubWidget_AudioMenu.h"
#include "SubWidget_GraphicsMenu.h"
#include "SubWidget_ControlsMenu.h"
#include "SubWidget_KeybindsMenu.h"

#include "BaseClass_PlayerController.generated.h"

// Forward Declarations
class UBaseClass_Widget_Options;
class UBaseClass_Widget_MainMenu;
class UBaseClass_Widget_SaveLoad;


UCLASS()
class THE_HAZARDS_API ABaseClass_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABaseClass_PlayerController();

protected:
	virtual void SetupInputComponent() override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_Options> OptionsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubwidget_AudioMenu> AudioMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_GraphicsMenu> GraphicsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_ControlsMenu> ControlsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_KeybindsMenu> KeybindsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_MainMenu> MainMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_SaveLoad> SaveLoad_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CurrentOpenMenuWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentOpenMenuWidget;

// ------------------------- Menus
	UPROPERTY()
	bool MainMenuMode;
};
