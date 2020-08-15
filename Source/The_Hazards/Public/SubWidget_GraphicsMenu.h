#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "GameFramework/GameUserSettings.h"
#include "UnrealEngine.h"
#include "RHI.h"

#include "SubWidget_GraphicsMenu.generated.h"

// Forward Declarations
class AEntity_Player;
class UBaseClass_Widget_Options;


UCLASS()
class THE_HAZARDS_API USubWidget_GraphicsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UButton* ApplySettingsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UComboBoxString* ResolutionDropdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UComboBoxString* FullscreenDropdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UCheckBox* VSyncCheckBox;

	// Brightness Slider
	// Framerate Limit
	// FPS Counter
	// Field of View / Camera Zoom

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf< UBaseClass_Widget_Options> Options_Class;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* PlayerReference;

// ------------------------- Variables
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
	//FScreenResolutionArray ValidResolutions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
	FVector2D CurrentPlayerScreenResolution;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
	FString CurrentPlayerScreenResolutionString;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void OpenWidget();

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

	UFUNCTION(BlueprintCallable)
	void ApplyGraphicsSettings();

	UFUNCTION(BlueprintCallable)
	void OnResolutionChanged();

	UFUNCTION(BlueprintCallable)
	void OnFullscreenChanged();

	UFUNCTION(BlueprintCallable)
	void OnVSyncChanged();
};
