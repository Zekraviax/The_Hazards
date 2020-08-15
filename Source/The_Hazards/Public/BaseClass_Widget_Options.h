#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseClass_Widget_PauseMenu.h"
#include "SubWidget_AudioMenu.h"
#include "SubWidget_GraphicsMenu.h"
#include "SubWidget_ControlsMenu.h"
#include "SubWidget_KeybindsMenu.h"
#include "Components/Image.h"

#include "BaseClass_Widget_Options.generated.h"

// Forward Declarations
class AEntity_Player_MainMenu;
class AEntity_Player;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_Options : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubwidget_AudioMenu> AudioMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_GraphicsMenu> GraphicsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_ControlsMenu> ControlsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_KeybindsMenu> KeybindsMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_PauseMenu> PauseMenu_Class;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	//TSubclassOf<UUserWidget> CurrentOpenMenuWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentOpenMenuWidget;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	//AActor* PlayerReference;
	AEntity_Player* PlayerReference;

// Functions
// --------------------------------------------------

// ------------------------- Sub-Menus
	UFUNCTION(BlueprintCallable)
	void OpenGraphicsMenu();

	UFUNCTION(BlueprintCallable)
	void OpenAudioMenu();

	UFUNCTION(BlueprintCallable)
	void OpenControlsMenu();

	UFUNCTION(BlueprintCallable)
	void OpenKeybindsMenu();

	UFUNCTION(BlueprintCallable)
	void CloseMenu();
};