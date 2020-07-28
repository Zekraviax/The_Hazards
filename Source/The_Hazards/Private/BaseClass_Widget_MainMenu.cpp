#include "BaseClass_Widget_MainMenu.h"


void UBaseClass_Widget_MainMenu::ResumeGame()
{

}


void UBaseClass_Widget_MainMenu::NewGame()
{

}


void UBaseClass_Widget_MainMenu::OpenLoadGameMenu()
{
	if (SaveLoad_Class) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SaveLoad>(GetWorld(), SaveLoad_Class);
		CurrentOpenMenuWidget->AddToViewport();
	}
}


void UBaseClass_Widget_MainMenu::OpenOptionsMenu()
{

}


void UBaseClass_Widget_MainMenu::QuitGame()
{
	FWindowsPlatformMisc::RequestExit(false);
}