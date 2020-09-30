#include "TheHazards_GameMode.h"

#include "BaseClass_Widget_LoadScreen.h"


void ATheHazards_GameMode::StartPlay()
{
	Super::StartPlay();
}


//void ATheHazards_GameMode::LoadSaveFile(USaveFile_Slot* SlotToLoad)
//{
//	if (LoadScreenWidget_Class) {
//		LoadScreenWidget_Reference = CreateWidget<UBaseClass_Widget_LoadScreen>(GetWorld(), LoadScreenWidget_Class);
//		LoadScreenWidget_Reference->AddToViewport();
//	}
//}