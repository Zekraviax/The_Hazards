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

}

void UBaseClass_Widget_PauseMenu::Function_QuitToDesktop()
{
	FWindowsPlatformMisc::RequestExit(false);
}