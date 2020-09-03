#include "BaseClass_Widget_SaveLoad.h"

#include "SaveFile_MetaList.h"


void UBaseClass_Widget_SaveLoad::GetSaveFiles(bool SaveMode)
{
	if (SaveLoadSlot_Class) {
		// Create New Save widget if SaveMode is true
		if (SaveMode) {
			SaveLoadSlot_Reference = CreateWidget<USubWidget_SaveLoadSlot>(GetWorld(), SaveLoadSlot_Class);
			SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_SaveNewSlot;
			SaveLoadSlot_Reference->SetSlotData();
			SaveFileScrollBox->AddChild(SaveLoadSlot_Reference);
		}

		// Get all existing saves, if any
		//FAsyncLoadGameFromSlotDelegate LoadDelegate;
		//LoadDelegate.BindUObject();
		if (USaveFile_MetaList* MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0))) {
			if (MetaList->SaveFileNames.Num() > 0) {
				for (int i = 0; i < MetaList->SaveFileNames.Num(); i++) {

				}
			}
		}
	}
}