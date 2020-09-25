#include "BaseClass_Widget_PauseMenu.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Entity_Player.h"


// Button Functions
void UBaseClass_Widget_PauseMenu::Function_ResumeGame()
{
	if (LocalPlayerReference)
		LocalPlayerReference->OpenPauseMenu();
}


void UBaseClass_Widget_PauseMenu::Function_QuitToMainMenu()
{
	//UGameplayStatics::UnloadStreamLevel();
}


void UBaseClass_Widget_PauseMenu::Function_QuitToDesktop()
{
	// Clean up all widgets and actors?
	//for (TObjectIterator<UWidget> Itr; Itr; ++Itr) {
	//	UWidget* FoundWidget = *Itr;

	//	if (FoundWidget->IsValidLowLevel())
	//		FoundWidget->RemoveFromParent();
	//}

	//for (TObjectIterator<AActor> Itr; Itr; ++Itr) {
	//	AActor* FoundActor = *Itr;

	//	if (FoundActor->IsValidLowLevel())
	//		FoundActor->Destroy();
	//}

	//FWindowsPlatformMisc::RequestExit(false);
	FGenericPlatformMisc::RequestExit(false);
	//UKismetSystemLibrary::QuitGame();
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
		Cast<UBaseClass_Widget_SaveLoad>(Player_Controller_Reference->CurrentOpenMenuWidget)->GetSaveFilesPartOne(SaveMode);
		Player_Controller_Reference->CurrentOpenMenuWidget->AddToViewport();
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = SaveLoadWidget_Class;
	}
}