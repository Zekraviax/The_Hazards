#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Slider.h"
#include "AudioDevice.h"
#include "Kismet/GameplayStatics.h"

#include "Subwidget_AudioMenu.generated.h"

// Forward Declarations
class AEntity_Player;
class ATheHazards_GameMode;
class UBaseClass_Widget_Options;

// Exclusive enum
UENUM(BlueprintType)
enum class E_VolumeSettingTypes : uint8
{
	E_MasterVolume,
	E_MusicVolume,
	E_AmbientVolume,
	E_EffectsVolume,
};


UCLASS()
class THE_HAZARDS_API USubwidget_AudioMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	USlider* MasterVolumeSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	USlider* MusicVolumeSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	USlider* EffectsVolumeSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	USlider* AmbientVolumeSlider;

	// Voice Volume

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf< UBaseClass_Widget_Options> Options_Class;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* PlayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ATheHazards_GameMode* GameModeReference;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void OpenWidget();

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

// ------------------------- Volume Settings
	UFUNCTION(BlueprintCallable)
	void OnVolumeChanged(E_VolumeSettingTypes Setting);
};
