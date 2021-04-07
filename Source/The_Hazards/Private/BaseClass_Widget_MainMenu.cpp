#include "BaseClass_Widget_MainMenu.h"

#include "Entity_Player_MainMenu.h"


void UBaseClass_Widget_MainMenu::ResumeGame()
{

}


void UBaseClass_Widget_MainMenu::NewGame()
{

<<<<<<< Updated upstream
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Add loading screen to player viewport
	if (LoadScreen_Class) {
		LoadScreen_Widget = CreateWidget<UBaseClass_Widget_LoadScreen>(GetWorld(), LoadScreen_Class);
		LoadScreen_Widget->AddToViewport();
	}

	// Load first level
	UGameplayStatics::LoadStreamLevel(GetWorld(), "Greybox1", true, true, LatentActionInfo);

	// Set main menu mode
	Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->MainMenuMode = false;

	RemoveFromParent();

	// Begin Minimum time delay for displaying the loading screen
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBaseClass_Widget_MainMenu::ClearLoadingScreen, 0.2f);
=======
>>>>>>> Stashed changes
}


void UBaseClass_Widget_MainMenu::OpenLoadGameMenu()
{
	if (SaveLoad_Class && PlayerReference) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SaveLoad>(GetWorld(), SaveLoad_Class);
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = SaveLoad_Class;
	}
}


void UBaseClass_Widget_MainMenu::OpenOptionsMenu()
{
	if (Options_Class && PlayerReference) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), Options_Class);
		Cast<UBaseClass_Widget_Options>(CurrentOpenMenuWidget)->PlayerReference = PlayerReference;
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = Options_Class;
	}
}


void UBaseClass_Widget_MainMenu::QuitGame()
{
	FWindowsPlatformMisc::RequestExit(false);
}