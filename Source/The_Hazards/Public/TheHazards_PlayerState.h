#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "SubWidget_AudioMenu.h"
#include "SubWidget_GraphicsMenu.h"
#include "SubWidget_ControlsMenu.h"
#include "SubWidget_KeybindsMenu.h"
#include "BaseClass_Widget_Options.h"
#include "BaseClass_Widget_MainMenu.h"
#include "BaseClass_Widget_SaveLoad.h"

#include "TheHazards_PlayerState.generated.h"

// Forward Declarations
//class UBaseClass_Widget_Options;
//class UBaseClass_Widget_MainMenu;
//class UBaseClass_Widget_SaveLoad;
//class USubwidget_AudioMenu;
//class USubWidget_ControlsMenu;
//class USubWidget_GraphicsMenu;
//class USubWidget_KeybindsMenu;

UCLASS()
class THE_HAZARDS_API ATheHazards_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
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
};
