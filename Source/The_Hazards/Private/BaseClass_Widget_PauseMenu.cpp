#include "BaseClass_Widget_PauseMenu.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Entity_Player.h"


// Button Functions
void UBaseClass_Widget_PauseMenu::Function_ResumeGame()
{
	if (LocalPlayerReference)
		LocalPlayerReference->OpenPauseMenu();
}


void UBaseClass_Widget_PauseMenu::Function_QuitToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}


void UBaseClass_Widget_PauseMenu::Function_QuitToDesktop()
{
	FWindowsPlatformMisc::RequestExit(false);
}


void UBaseClass_Widget_PauseMenu::OpenOptionsMenu()
{
	if (LocalPlayerReference && OptionsWidget_Class) {
		LocalPlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		LocalPlayerReference->CurrentOpenMenuWidget = NULL;
		LocalPlayerReference->CurrentOpenMenuWidget_Class = NULL;

		LocalPlayerReference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), OptionsWidget_Class);
		Cast<UBaseClass_Widget_Options>(LocalPlayerReference->CurrentOpenMenuWidget)->PlayerReference = LocalPlayerReference;
		LocalPlayerReference->CurrentOpenMenuWidget->AddToViewport();
		LocalPlayerReference->CurrentOpenMenuWidget_Class = OptionsWidget_Class;
	}
}


void UBaseClass_Widget_PauseMenu::OpenSaveLoadMenu(bool SaveMode)
{
	if (LocalPlayerReference && SaveLoadWidget_Class) {
		LocalPlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		LocalPlayerReference->CurrentOpenMenuWidget = NULL;
		LocalPlayerReference->CurrentOpenMenuWidget_Class = NULL;

		LocalPlayerReference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SaveLoad>(GetWorld(), SaveLoadWidget_Class);
		Cast<UBaseClass_Widget_SaveLoad>(LocalPlayerReference->CurrentOpenMenuWidget)->PlayerReference = LocalPlayerReference;
		Cast<UBaseClass_Widget_SaveLoad>(LocalPlayerReference->CurrentOpenMenuWidget)->GetSaveFiles(SaveMode);
		LocalPlayerReference->CurrentOpenMenuWidget->AddToViewport();
		LocalPlayerReference->CurrentOpenMenuWidget_Class = SaveLoadWidget_Class;
	}
}