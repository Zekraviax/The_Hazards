#include "BaseClass_Widget_Options.h"

#include "Entity_Player_MainMenu.h"
#include "SaveFile_Settings.h"


void UBaseClass_Widget_Options::OpenGraphicsMenu()
{
	if (GraphicsMenu_Class && PlayerReference) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget = NULL;
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;

		CurrentOpenMenuWidget = CreateWidget<USubWidget_GraphicsMenu>(GetWorld(), GraphicsMenu_Class);
		Cast<USubWidget_GraphicsMenu>(CurrentOpenMenuWidget)->PlayerReference = PlayerReference;
		Cast<USubWidget_GraphicsMenu>(CurrentOpenMenuWidget)->OpenWidget();
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = GraphicsMenu_Class;
	}
}

void UBaseClass_Widget_Options::OpenAudioMenu()
{
	if (AudioMenu_Class && PlayerReference) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget = NULL;
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;

		CurrentOpenMenuWidget = CreateWidget<USubwidget_AudioMenu>(GetWorld(), AudioMenu_Class);
		Cast<USubwidget_AudioMenu>(CurrentOpenMenuWidget)->PlayerReference = PlayerReference;
		Cast<USubwidget_AudioMenu>(CurrentOpenMenuWidget)->OpenWidget();
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = AudioMenu_Class;
	}
}


void UBaseClass_Widget_Options::OpenControlsMenu()
{
	if (ControlsMenu_Class && PlayerReference) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;
		PlayerReference->CurrentOpenMenuWidget = NULL;

		CurrentOpenMenuWidget = CreateWidget<USubWidget_ControlsMenu>(GetWorld(), ControlsMenu_Class);
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = ControlsMenu_Class;
	}
}


void UBaseClass_Widget_Options::OpenKeybindsMenu()
{
	if (KeybindsMenu_Class && PlayerReference) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget = NULL;
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;

		CurrentOpenMenuWidget = CreateWidget<USubWidget_KeybindsMenu>(GetWorld(), KeybindsMenu_Class);
		Cast<USubWidget_KeybindsMenu>(CurrentOpenMenuWidget)->PlayerReference = PlayerReference;

		if (!Cast<USubWidget_KeybindsMenu>(CurrentOpenMenuWidget)->Options_Class)
			Cast<USubWidget_KeybindsMenu>(CurrentOpenMenuWidget)->Options_Class = this->GetClass();

		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = KeybindsMenu_Class;

		Cast<USubWidget_KeybindsMenu>(CurrentOpenMenuWidget)->OpenWidget();
	}
}


void UBaseClass_Widget_Options::CloseMenu()
{
	if (PlayerReference) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget = NULL;
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;

		// Chcek if the player is on the main menu level
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Level: %s"), *PlayerReference->GetLevel()->GetName()));

		//if (PlayerReference->GetLevel()->GetName() != "MainMenu" && PauseMenu_Class) {
		if (PauseMenu_Class) {
			//UGameplayStatics::SetGamePaused(GetWorld(), false);
			CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_PauseMenu>(GetWorld(), PauseMenu_Class);
			Cast<UBaseClass_Widget_PauseMenu>(CurrentOpenMenuWidget)->LocalPlayerReference = PlayerReference;
			CurrentOpenMenuWidget->AddToViewport();

			PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
			PlayerReference->CurrentOpenMenuWidget_Class = PauseMenu_Class;
		}

		// Save Settings
	}
}