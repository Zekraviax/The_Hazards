#include "BaseClass_Widget_MainMenu.h"

#include "Entity_Player_MainMenu.h"


void UBaseClass_Widget_MainMenu::ResumeGame()
{

}


void UBaseClass_Widget_MainMenu::NewGame()
{

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


//void UBaseClass_Widget_MainMenu::OpenSaveLoadMenu(bool SaveMode)
//{
//
//}