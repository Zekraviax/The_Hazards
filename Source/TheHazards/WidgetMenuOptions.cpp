#include "WidgetMenuOptions.h"


#include "SaveGameOptions.h"
#include "TheHazardsGameInstance.h"
#include "TheHazardsVariables.h"


void UWidgetMenuOptions::LoadOptions()
{
	USaveGameOptions* OptionsSaveObject = Cast<UTheHazardsGameInstance>(GetGameInstance())->GetOptionsSaveObject();

	MasterVolumeSlider->SetValue(OptionsSaveObject->OptionsData.MasterVolumeValue);
}


void UWidgetMenuOptions::OnMasterVolumeSliderValueUpdated(float NewValue)
{
	Cast<UTheHazardsGameInstance>(GetGameInstance())->GetOptionsSaveObject()->OptionsData.MasterVolumeValue = NewValue;
}


void UWidgetMenuOptions::SaveOptions()
{

}