#include "BaseClass_Widget_DevMenu.h"

#include "Entity_Player.h"


// ------------------------- Widget
void UBaseClass_Widget_DevMenu::OpenWidget()
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	UpdateVariables();
}


void UBaseClass_Widget_DevMenu::UpdateVariables()
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	PlayerLevelText->SetText(FText::FromString(FString::FromInt(PlayerReference->Level)));
}


// ------------------------- Button Functions
void UBaseClass_Widget_DevMenu::ChangePlayerLevel(int LevelChangeValue)
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	PlayerReference->Level += LevelChangeValue;
	UpdateVariables();
}