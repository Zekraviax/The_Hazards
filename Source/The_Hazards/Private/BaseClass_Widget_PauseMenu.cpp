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
	//UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	//UGameplayStatics::UnloadStreamLevel();
}


void UBaseClass_Widget_PauseMenu::Function_QuitToDesktop()
{
	FWindowsPlatformMisc::RequestExit(false);
}


void UBaseClass_Widget_PauseMenu::OpenOptionsMenu()
{
	if (!Player_Controller_Reference && GetWorld()) {
		Player_Controller_Reference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}

	if (Player_Controller_Reference && OptionsWidget_Class) {
		Player_Controller_Reference->CurrentOpenMenuWidget->RemoveFromParent();
		Player_Controller_Reference->CurrentOpenMenuWidget = NULL;
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = NULL;

		Player_Controller_Reference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), OptionsWidget_Class);
		//Cast<UBaseClass_Widget_Options>(Player_Controller_Reference->CurrentOpenMenuWidget)->PlayerReference = LocalPlayerReference;
		Player_Controller_Reference->CurrentOpenMenuWidget->AddToViewport();
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = OptionsWidget_Class;
	}
}


void UBaseClass_Widget_PauseMenu::OpenSaveLoadMenu(bool SaveMode)
{
	if (!Player_Controller_Reference && GetWorld()) {
		Player_Controller_Reference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}

	if (Player_Controller_Reference && SaveLoadWidget_Class) {
		if (Player_Controller_Reference->CurrentOpenMenuWidget)
			Player_Controller_Reference->CurrentOpenMenuWidget->RemoveFromParent();

		Player_Controller_Reference->CurrentOpenMenuWidget = NULL;
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = NULL;

		Player_Controller_Reference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SaveLoad>(GetWorld(), SaveLoadWidget_Class);
		//Cast<UBaseClass_Widget_SaveLoad>(Player_Controller_Reference->CurrentOpenMenuWidget)->PlayerReference = LocalPlayerReference;
		Cast<UBaseClass_Widget_SaveLoad>(Player_Controller_Reference->CurrentOpenMenuWidget)->GetSaveFiles(SaveMode);
		Player_Controller_Reference->CurrentOpenMenuWidget->AddToViewport();
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = SaveLoadWidget_Class;
	}
}