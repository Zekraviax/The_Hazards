#include "SubWidget_KeybindsMenu.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "SubWidget_KeyRebindButton.h"


void USubWidget_KeybindsMenu::OpenWidget()
{
	InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	// Get all KeyRebindButtons and set their KeybindsMenu reference to this
	for (TObjectIterator<USubWidget_KeyRebindButton> Itr; Itr; ++Itr) {
		USubWidget_KeyRebindButton *FoundWidget = *Itr;

		if (!FoundWidget->KeybindsMenuReference) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Found KeyRebindButton")));
			FoundWidget->KeybindsMenuReference = this;

			if (FoundWidget->KeyName->IsValidLowLevel()) {
				if (FoundWidget->IsAxisMapping) {
					TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->AxisMappings;

					for (FInputAxisKeyMapping& Key : AxisMappings) {
						if (Key.AxisName.ToString() == FoundWidget->MappingName.ToString()) {
							FoundWidget->KeyName->SetText(Key.Key.GetDisplayName());
							break;
						}
					}
				} else {
					TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->ActionMappings;

					for (FInputActionKeyMapping& Key : ActionMappings) {
						if (Key.ActionName.ToString() == FoundWidget->MappingName.ToString()) {
							//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, FString::Printf(TEXT("Action Key: %s"), *Key.ActionName.ToString()));
							FoundWidget->KeyName->SetText(Key.Key.GetDisplayName());
							break;
						}
						//else {
						//	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, FString::Printf(TEXT("%s != %s"), *Key.ActionName.ToString(), *FoundWidget->MappingName.ToString()));
						//}
					}
				}
			} 
		}
	}
}


void USubWidget_KeybindsMenu::CloseWidget()
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


void USubWidget_KeybindsMenu::RebindAxisKey(FInputAxisKeyMapping AxisKey)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Rebind Axis Key")));

	if (!InputSettings->IsValidLowLevel())
		InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	//if (!InputSettings)
	//	return false;

	if (InputSettings) {
		TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->AxisMappings;

		for (FInputAxisKeyMapping& Key : AxisMappings) {
			if (Key.AxisName.ToString() == KeyName.ToString()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found %s"), *Key.AxisName.ToString()));

				InputSettings->RemoveAxisMapping(Key, false);
				InputSettings->AddAxisMapping(FInputAxisKeyMapping(KeyName, AxisKey.Key, KeyAxisScale), true);

				if (!ApplyButton->bIsEnabled) {
					ApplyButton->SetIsEnabled(true);
				}

				CancelRebindKey();
				break;
			}
		}
	}
}


void USubWidget_KeybindsMenu::RebindActionKey(FInputActionKeyMapping ActionKey)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Rebind Action Key")));

	if (!InputSettings->IsValidLowLevel())
		InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	//if (!InputSettings)
	//	return false;

	if (InputSettings) {
		TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->ActionMappings;

		for (FInputActionKeyMapping& Key : ActionMappings) {
			if (Key.ActionName.ToString() == KeyName.ToString()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found %s"), *Key.ActionName.ToString()));

				InputSettings->RemoveActionMapping(Key, false);
				InputSettings->AddActionMapping(FInputActionKeyMapping(KeyName, ActionKey.Key, false, false, false, false), true);

				// Enable apply button
				if (!ApplyButton->bIsEnabled) {
					ApplyButton->SetIsEnabled(true);
				}

				CancelRebindKey();
				break;
			}
		}
	}
}


void USubWidget_KeybindsMenu::CancelRebindKey()
{
	this->bIsFocusable = false;
	Cast<ABaseClass_PlayerController>(PlayerReference->GetController())->SetInputMode(FInputModeGameOnly());
}


void USubWidget_KeybindsMenu::ApplyReboundKeys()
{
	InputSettings->ForceRebuildKeymaps();
	InputSettings->SaveKeyMappings();

	if (ApplyButton->bIsEnabled) {
		ApplyButton->SetIsEnabled(false);
	}
}