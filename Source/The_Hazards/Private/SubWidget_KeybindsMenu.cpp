#include "SubWidget_KeybindsMenu.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "SubWidget_KeyRebindButton.h"


void USubWidget_KeybindsMenu::OpenWidget()
{
	InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	TArray<FInputAxisKeyMapping> AxisKeybindsArray;
	TArray<FInputActionKeyMapping> ActionKeybindsArray;

	// Get all KeyRebindButtons and set their KeybindsMenu reference to this
	for (TObjectIterator<USubWidget_KeyRebindButton> Itr; Itr; ++Itr) {
		USubWidget_KeyRebindButton *FoundWidget = *Itr;

		FoundWidget->KeybindsMenuReference = this;

		if (FoundWidget->KeyName->IsValidLowLevel()) {
			if (FoundWidget->IsAxisMapping) {
				AxisKeybindsArray = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeysForAxis(FoundWidget->MappingName);
				if (FoundWidget->IsPrimaryKey && AxisKeybindsArray.IsValidIndex(0)) {
					FoundWidget->KeyName->SetText(AxisKeybindsArray[0].Key.GetDisplayName());
					FoundWidget->AxisKey = AxisKeybindsArray[0];
				} else {
					if (AxisKeybindsArray.IsValidIndex(1)) {
						FoundWidget->KeyName->SetText(AxisKeybindsArray[1].Key.GetDisplayName());
						FoundWidget->AxisKey = AxisKeybindsArray[1];
					} else {
						FoundWidget->KeyName->SetText(FText::FromString("None"));
					}
				}
			} else {
				ActionKeybindsArray = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeysForAction(FoundWidget->MappingName);
				if (FoundWidget->IsPrimaryKey && ActionKeybindsArray.IsValidIndex(0)) {
					FoundWidget->KeyName->SetText(ActionKeybindsArray[0].Key.GetDisplayName());
					FoundWidget->ActionKey = ActionKeybindsArray[0];
				}
				else {
					if (ActionKeybindsArray.IsValidIndex(1)) {
						FoundWidget->KeyName->SetText(ActionKeybindsArray[1].Key.GetDisplayName());
						FoundWidget->ActionKey = ActionKeybindsArray[1];
					}
					else {
						FoundWidget->KeyName->SetText(FText::FromString("None"));
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
	if (!InputSettings->IsValidLowLevel())
		InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	//if (!InputSettings)
	//	return false;

	TArray<FInputAxisKeyMapping> AxisKeybindsArray = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeysForAxis(KeyName);

	if (InputSettings) {
		TArray<FInputAxisKeyMapping> AxisMappings = InputSettings->GetAxisMappings();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Rebind Axis Key")));

		for (FInputAxisKeyMapping& Key : AxisMappings) {
			if (KeyIsPrimary && AxisKeybindsArray.IsValidIndex(0)) {
				if (Key.AxisName.ToString() == AxisKeybindsArray[0].AxisName.ToString()) {
					//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Found %s"), *Key.AxisName.ToString()));
					//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Key: %s"), *AxisKeybindsArray[0].Key.GetDisplayName().ToString()));

					InputSettings->RemoveAxisMapping(Key, false);
					InputSettings->AddAxisMapping(FInputAxisKeyMapping(KeyName, AxisKey.Key, KeyAxisScale), true);

					if (CurrentSelectedButton->IsValidLowLevel()) {
						CurrentSelectedButton->AxisKey = AxisKey;
					}

					if (!ApplyButton->bIsEnabled) {
						ApplyButton->SetIsEnabled(true);
					}

					CancelRebindKey();
					break;
				}
			} else if (AxisKeybindsArray.IsValidIndex(1)) {
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Found %s"), *Key.Key.GetDisplayName().ToString()));
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Key: %s"), *AxisKeybindsArray[1].Key.GetDisplayName().ToString()));

				if (Key.Key.GetDisplayName().ToString() == AxisKeybindsArray[1].Key.GetDisplayName().ToString()) {
					InputSettings->RemoveAxisMapping(Key, false);
					InputSettings->AddAxisMapping(FInputAxisKeyMapping(KeyName, AxisKey.Key, KeyAxisScale), true);

					if (CurrentSelectedButton->IsValidLowLevel()) {
						CurrentSelectedButton->AxisKey = AxisKey;
					}

					if (!ApplyButton->bIsEnabled) {
						ApplyButton->SetIsEnabled(true);
					}

					CancelRebindKey();
					break;
				}
			} else {
				//CancelRebindKey();
			}
		}
	}

	if (ApplyButton->bIsEnabled) {
		for (TObjectIterator<USubWidget_KeyRebindButton> Itr; Itr; ++Itr) {
			USubWidget_KeyRebindButton *FoundWidget = *Itr;
			FoundWidget->UpdateText();
		}
	}
}


void USubWidget_KeybindsMenu::RebindActionKey(FInputActionKeyMapping ActionKey)
{
	if (!InputSettings->IsValidLowLevel())
		InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	//if (!InputSettings)
	//	return false;

	TArray<FInputActionKeyMapping> ActionKeybindsArray = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeysForAction(KeyName);

	if (InputSettings) {
		TArray<FInputActionKeyMapping> ActionMappings = InputSettings->GetActionMappings();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Rebind Action Key")));

		for (FInputActionKeyMapping& Key : ActionMappings) {
			if (KeyIsPrimary && ActionKeybindsArray.IsValidIndex(0)) {
				if (Key.ActionName.ToString() == ActionKeybindsArray[0].ActionName.ToString()) {
					//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Found %s"), *Key.ActionName.ToString()));

					InputSettings->RemoveActionMapping(Key, false);
					InputSettings->AddActionMapping(FInputActionKeyMapping(KeyName, ActionKey.Key, false, false, false, false), true);

					if (CurrentSelectedButton->IsValidLowLevel()) {
						CurrentSelectedButton->ActionKey = ActionKey;
					}

					if (!ApplyButton->bIsEnabled) {
						ApplyButton->SetIsEnabled(true);
					}

					CancelRebindKey();
					break;
				}
			}
			else if (ActionKeybindsArray.IsValidIndex(1)) {
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Found %s"), *Key.Key.GetDisplayName().ToString()));
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Key: %s"), *ActionKeybindsArray[1].Key.GetDisplayName().ToString()));

				if (Key.Key.GetDisplayName().ToString() == ActionKeybindsArray[1].Key.GetDisplayName().ToString()) {
					InputSettings->RemoveActionMapping(Key, false);
					InputSettings->AddActionMapping(FInputActionKeyMapping(KeyName, ActionKey.Key, false, false, false, false), true);

					if (CurrentSelectedButton->IsValidLowLevel()) {
						CurrentSelectedButton->ActionKey = ActionKey;
					}

					if (!ApplyButton->bIsEnabled) {
						ApplyButton->SetIsEnabled(true);
					}

					CancelRebindKey();
					break;
				}
			}
			else {
				//CancelRebindKey();
			}
		}
	}

	if (ApplyButton->bIsEnabled) {
		for (TObjectIterator<USubWidget_KeyRebindButton> Itr; Itr; ++Itr) {
			USubWidget_KeyRebindButton *FoundWidget = *Itr;
			FoundWidget->UpdateText();
		}
	}
}


void USubWidget_KeybindsMenu::RebindAnyKey(FKey Key)
{
	if (CurrentSelectedButton) {
		if (CurrentSelectedButton->IsAxisMapping) {
			FInputAxisKeyMapping AxisMapping;

			AxisMapping.AxisName = KeyName;
			AxisMapping.Scale = KeyAxisScale;
			AxisMapping.Key = Key;

			RebindAxisKey(AxisMapping);
		}
		else {
			FInputActionKeyMapping ActionMapping;

			ActionMapping.ActionName = KeyName;
			ActionMapping.Key = Key;

			RebindActionKey(ActionMapping);
		}
	} 
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CurrentSelectedButton Error")));
	}
}


void USubWidget_KeybindsMenu::CancelRebindKey()
{
	//this->bIsFocusable = false;
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