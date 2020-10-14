#include "BaseClass_Widget_DevMenu.h"

#include "Entity_Player.h"


void UBaseClass_Widget_DevMenu::ChangePlayerLevel(int LevelChangeValue)
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	PlayerReference->Level += LevelChangeValue;
}