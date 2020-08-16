#include "SubWidget_KeyRebindButton.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "SubWidget_KeybindsMenu.h"


void USubWidget_KeyRebindButton::OnKeybindMenuOpen()
{
	//KeyName->SetText(FText::FromName(MappingName));
}


void USubWidget_KeyRebindButton::EnableRebindKeyMode()
{
	if (KeybindsMenuReference) {
		if (KeybindsMenuReference->PlayerReference) {
			KeybindsMenuReference->bIsFocusable = true;
			Cast<ABaseClass_PlayerController>(KeybindsMenuReference->PlayerReference->GetController())->SetInputMode(FInputModeUIOnly());

			KeybindsMenuReference->KeyName = MappingName;
			KeybindsMenuReference->KeyIsAxis = IsAxisMapping;
			KeybindsMenuReference->KeyAxisScale = AxisMappingScale;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Press any key except Escape to rebind."));
		}
	}
}