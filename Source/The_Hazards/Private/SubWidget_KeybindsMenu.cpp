#include "SubWidget_KeybindsMenu.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "SubWidget_KeyRebindButton.h"


void USubWidget_KeybindsMenu::OpenWidget()
{
	// Get all KeyRebindButtons and set their KeybindsMenu reference to this
	for (TObjectIterator<USubWidget_KeyRebindButton> Itr; Itr; ++Itr) {
		USubWidget_KeyRebindButton *FoundWidget = *Itr;

		if (!FoundWidget->KeybindsMenuReference) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Found KeyRebindButton")));
			FoundWidget->KeybindsMenuReference = this;
			//FoundWidget->OnKeybindMenuOpen();
			//FoundWidget->KeyName->SetText(FText::FromString("a"));
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Rebind Axis Key")));

	UInputSettings* InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	//if (!InputSettings)
	//	return false;

	if (InputSettings) {
		TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->AxisMappings;

		for (FInputAxisKeyMapping& Key : AxisMappings) {
			if (Key.AxisName.ToString() == KeyName.ToString()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found %s"), *Key.AxisName.ToString()));

				InputSettings->RemoveAxisMapping(Key, false);
				InputSettings->AddAxisMapping(FInputAxisKeyMapping(KeyName, AxisKey.Key, KeyAxisScale), true);

				CancelRebindKey();
				break;
			}
		}
	}
}


void USubWidget_KeybindsMenu::RebindActionKey(FInputActionKeyMapping ActionKey)
{

}


void USubWidget_KeybindsMenu::CancelRebindKey()
{
	this->bIsFocusable = false;
	Cast<ABaseClass_PlayerController>(PlayerReference->GetController())->SetInputMode(FInputModeGameOnly());
}