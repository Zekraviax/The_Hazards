#include "SubWidget_KeybindsMenu.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "SubWidget_KeyRebindButton.h"


void USubWidget_KeybindsMenu::OpenWidget()
{
	// Get all KeyRebindButtons and set their KeybindsMenu reference to this
	for (TObjectIterator<USubWidget_KeyRebindButton> Itr; Itr; ++Itr) {
		USubWidget_KeyRebindButton *FoundWidget = *Itr;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Found KeyRebindButton")));

		if (FoundWidget->KeybindsMenuReference)
			FoundWidget->KeybindsMenuReference = this;
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

}


void USubWidget_KeybindsMenu::RebindActionKey(FInputActionKeyMapping ActionKey)
{

}


void USubWidget_KeybindsMenu::CancelRebindKey()
{
	this->bIsFocusable = false;
	Cast<ABaseClass_PlayerController>(PlayerReference->GetController())->SetInputMode(FInputModeUIOnly());
}