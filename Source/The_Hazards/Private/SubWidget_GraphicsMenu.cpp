#include "SubWidget_GraphicsMenu.h"

#include "Entity_Player.h"


void USubWidget_GraphicsMenu::OpenWidget()
{
	FScreenResolutionArray ValidResolutions;

	// Set Resolution Settings
	if (RHIGetAvailableResolutions(ValidResolutions, false)) {
		// Get player resolution
		CurrentPlayerScreenResolution.X = GSystemResolution.ResX;
		CurrentPlayerScreenResolution.Y = GSystemResolution.ResY;

		for (const FScreenResolutionRHI& Resolution : ValidResolutions) {
			// Convert resolution to string
			FString ResolutionString = FString::FromInt(Resolution.Width) + " x " + FString::FromInt(Resolution.Height) + "  /  " + FString::FromInt(Resolution.RefreshRate) + "Hz";

			// Add resolution string to resolution dropdown
			ResolutionDropdown->AddOption(ResolutionString);

			// Check for the player's current screen resolution
			if (Resolution.Width == CurrentPlayerScreenResolution.X && Resolution.Height == CurrentPlayerScreenResolution.Y) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Found Player Screen Resolution"));
				ResolutionDropdown->SetSelectedOption(ResolutionString);

			}
		}
	}

	// Set Fullscreen Settings
	// 0 = Fullscreen
	// 1 = Windowed Fullscreen
	// 2 = Windowed
	switch (GEngine->GameUserSettings->GetFullscreenMode()) {
		case(EWindowMode::Fullscreen):
			FullscreenDropdown->SetSelectedIndex(0);
			break;
		case(EWindowMode::WindowedFullscreen):
			FullscreenDropdown->SetSelectedIndex(1);
			break;
		case(EWindowMode::Windowed):
			FullscreenDropdown->SetSelectedIndex(2);
			break;
		default:
			FullscreenDropdown->SetSelectedIndex(2);
			break;
	}
}


void USubWidget_GraphicsMenu::CloseWidget()
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


void USubWidget_GraphicsMenu::ApplyGraphicsSettings()
{
	GEngine->GameUserSettings->ApplyResolutionSettings(false);

	// Disable apply settings button
	// Re-enable apply settings button when any setting is changed
	// If the button is enabled, display a prompt when the user tries to leave the widget without comfirming the settings change(s)
	ApplySettingsButton->SetIsEnabled(false);
}


void USubWidget_GraphicsMenu::OnResolutionChanged()
{
	FScreenResolutionArray ValidResolutions;

	if (RHIGetAvailableResolutions(ValidResolutions, false)) {
		for (const FScreenResolutionRHI& Resolution : ValidResolutions) {
			FString ResolutionString = FString::FromInt(Resolution.Width) + " x " + FString::FromInt(Resolution.Height) + "  /  " + FString::FromInt(Resolution.RefreshRate) + "Hz";

			if (ResolutionString == ResolutionDropdown->GetSelectedOption()) {
				FIntPoint NewResolution = FIntPoint(Resolution.Width, Resolution.Height);
				GEngine->GameUserSettings->SetScreenResolution(NewResolution);

				if (!ApplySettingsButton->GetIsEnabled()) {
					ApplySettingsButton->SetIsEnabled(true);
				}
			}
		}
	}
}


void USubWidget_GraphicsMenu::OnFullscreenChanged()
{
	if (FullscreenDropdown->GetSelectedOption() == "Fullscreen") {
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	} else if (FullscreenDropdown->GetSelectedOption() == "Borderless Fullscreen") {
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	} else if (FullscreenDropdown->GetSelectedOption() == "Windowed") {
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	} else {
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	}

	if (!ApplySettingsButton->GetIsEnabled()) {
		ApplySettingsButton->SetIsEnabled(true);
	}
}


void USubWidget_GraphicsMenu::OnVSyncChanged()
{
	GEngine->GameUserSettings->SetVSyncEnabled(VSyncCheckBox->IsChecked());

	if (!ApplySettingsButton->GetIsEnabled()) {
		ApplySettingsButton->SetIsEnabled(true);
	}
}