#include "SubWidget_KeyRebindButton.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "SubWidget_KeybindsMenu.h"


void USubWidget_KeyRebindButton::OnKeybindMenuOpen()
{

}


void USubWidget_KeyRebindButton::UpdateText()
{
	if (KeyName->IsValidLowLevel()) {
		if (AxisKey.Key.IsValid())
			KeyName->SetText(AxisKey.Key.GetDisplayName());
		else if (ActionKey.Key.IsValid())
			KeyName->SetText(ActionKey.Key.GetDisplayName());
		else
			KeyName->SetText(FText::FromString("None"));
	}
}


void USubWidget_KeyRebindButton::EnableRebindKeyMode()
{
	if (KeybindsMenuReference) {
		if (KeybindsMenuReference->PlayerReference) {
			KeybindsMenuReference->PlayerReference->LockMenuButtonActions = true;

			KeybindsMenuReference->bIsFocusable = true;
			Cast<ABaseClass_PlayerController>(KeybindsMenuReference->PlayerReference->GetController())->SetInputMode(FInputModeUIOnly());

			KeybindsMenuReference->KeyName = MappingName;
			KeybindsMenuReference->KeyIsAxis = IsAxisMapping;
			KeybindsMenuReference->KeyIsPrimary = IsPrimaryKey;
			KeybindsMenuReference->KeyAxisScale = AxisMappingScale;
			KeybindsMenuReference->CurrentSelectedButton = this;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Press any key except Escape to rebind."));
		}
	}
}