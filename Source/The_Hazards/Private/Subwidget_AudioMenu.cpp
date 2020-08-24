#include "Subwidget_AudioMenu.h"


void USubwidget_AudioMenu::OpenWidget()
{
	if (!GameModeReference)
		GameModeReference = Cast<ATheHazards_GameMode>(GetWorld()->GetAuthGameMode());

	// Set slider values
	MasterVolumeSlider->SetValue(GameModeReference->VolumeSettings.MasterVolume);
	MusicVolumeSlider->SetValue(GameModeReference->VolumeSettings.MusicVolume);
	EffectsVolumeSlider->SetValue(GameModeReference->VolumeSettings.EffectsVolume);
	AmbientVolumeSlider->SetValue(GameModeReference->VolumeSettings.AmbientVolume);
}


void USubwidget_AudioMenu::CloseWidget()
{
	if (PlayerReference && Options_Class) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget = NULL;
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;

		PlayerReference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), Options_Class);
		Cast<UBaseClass_Widget_Options>(PlayerReference->CurrentOpenMenuWidget)->PlayerReference = PlayerReference;
		PlayerReference->CurrentOpenMenuWidget->AddToViewport();
		PlayerReference->CurrentOpenMenuWidget_Class = Options_Class;
	}
}


void USubwidget_AudioMenu::OnVolumeChanged(E_VolumeSettingTypes Setting)
{
	if (!GameModeReference)
		GameModeReference = Cast<ATheHazards_GameMode>(GetWorld()->GetAuthGameMode());

	switch (Setting) {
		case(E_VolumeSettingTypes::E_MasterVolume):
			GameModeReference->VolumeSettings.MasterVolume = MasterVolumeSlider->GetValue();
			break;
		case(E_VolumeSettingTypes::E_MusicVolume):
			GameModeReference->VolumeSettings.MusicVolume = MusicVolumeSlider->GetValue();
			break;
		case(E_VolumeSettingTypes::E_EffectsVolume):
			GameModeReference->VolumeSettings.EffectsVolume = EffectsVolumeSlider->GetValue();
			break;
		case(E_VolumeSettingTypes::E_AmbientVolume):
			GameModeReference->VolumeSettings.AmbientVolume = AmbientVolumeSlider->GetValue();
			break;
		default:
			break;
	}
}