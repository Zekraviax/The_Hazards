#include "TheHazards_GameInstance.h"

#include "SaveFile_Slot.h"


void UTheHazards_GameInstance::LoadSaveFile(USaveFile_Slot* SlotReference)
{
	TArray<UUserWidget*> WidgetsToRemove;
	FStreamableManager StreamableManager;

	for (TObjectIterator<UUserWidget> Itr; Itr; ++Itr) {
		UUserWidget* FoundWidget = *Itr;
		WidgetsToRemove.Add(FoundWidget);
	}

	// Create and display a Loading Screen
	if (LoadScreen_Class) {
		LoadScreen_Widget = CreateWidget<UBaseClass_Widget_LoadScreen>(GetWorld(), LoadScreen_Class);
		LoadScreen_Widget->AddToViewport();
	}

	for (auto Widget : WidgetsToRemove) {
		Widget->RemoveFromParent();
	}

	// Async load level
	//StreamableManager.RequestAsyncLoad();
}