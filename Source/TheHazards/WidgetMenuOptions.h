#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "TheHazardsVariables.h"

#include "WidgetMenuOptions.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetMenuOptions : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionsData OptionsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* MasterVolumeSlider;

	UFUNCTION()
	void LoadOptions();

	UFUNCTION(BlueprintCallable)
	void OnMasterVolumeSliderValueUpdated(float NewValue);

	UFUNCTION(BlueprintCallable)
	void SaveOptions();
};