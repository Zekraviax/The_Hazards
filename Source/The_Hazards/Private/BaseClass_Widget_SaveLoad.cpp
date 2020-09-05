#include "BaseClass_Widget_SaveLoad.h"

#include "SaveFile_MetaList.h"
#include "SaveFile_Slot.h"

void UBaseClass_Widget_SaveLoad::GetSaveFiles(bool SaveMode)
{
	// Clear the SaveFileScrollBox widget
	SaveFileScrollBox->ClearChildren();

	if (SaveLoadSlot_Class) {
		// Create New Save widget if SaveMode is true
		if (SaveMode) {
			SaveLoadSlot_Reference = CreateWidget<USubWidget_SaveLoadSlot>(GetWorld(), SaveLoadSlot_Class);
			SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_SaveNewSlot;

			// Set New Save texts
			SaveLoadSlot_Reference->SlotNameText->SetText(FText::FromString("New Save"));
			SaveLoadSlot_Reference->CharacterNameText->SetText(FText::FromString(""));
			SaveLoadSlot_Reference->LevelText->SetText(FText::FromString(""));
			SaveLoadSlot_Reference->PlaytimeText->SetText(FText::FromString(""));
			SaveLoadSlot_Reference->DateSavedText->SetText(FText::FromString(""));
			SaveLoadSlot_Reference->SlotNumberText->SetText(FText::FromString(""));
			SaveLoadSlot_Reference->SaveCountText->SetText(FText::FromString(""));

			SaveLoadSlot_Reference->SetSlotData();
			SaveFileScrollBox->AddChild(SaveLoadSlot_Reference);
		}

		// Get all existing saves, if any
		//FAsyncLoadGameFromSlotDelegate LoadDelegate;
		//LoadDelegate.BindUObject();
		if (USaveFile_MetaList* MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0))) {
			if (MetaList->SaveFileNames.Num() > 0) {
				for (int i = 0; i < MetaList->SaveFileNames.Num(); i++) {
					// Load Save Slots for texts
					if (USaveFile_Slot* LoadedSlot = Cast<USaveFile_Slot>(UGameplayStatics::LoadGameFromSlot(MetaList->SaveFileNames[i], 0))) {
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Found slot %s"), *MetaList->SaveFileNames[i]));

						SaveLoadSlot_Reference = CreateWidget<USubWidget_SaveLoadSlot>(GetWorld(), SaveLoadSlot_Class);

						if (SaveMode)
							SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_SaveExistingSlot;
						else
							SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_LoadExistingSLot;

						SaveLoadSlot_Reference->SetSlotData();

						// Set Save Slot texts
						SaveLoadSlot_Reference->SlotNameText->SetText(FText::FromString(MetaList->SaveFileNames[i]));
						SaveLoadSlot_Reference->CharacterNameText->SetText(FText::FromString(LoadedSlot->PlayerReference->CharacterSheet.Name));
						SaveLoadSlot_Reference->LevelText->SetText(FText::FromString("Level " + FString::FromInt(LoadedSlot->PlayerReference->Level)));
						SaveLoadSlot_Reference->PlaytimeText->SetText(FText::FromString("00:00"));
						SaveLoadSlot_Reference->DateSavedText->SetText(FText::FromString(LoadedSlot->DateSaved.ToString()));
						SaveLoadSlot_Reference->SlotNumberText->SetText(FText::FromString("Slot " + FString::FromInt(i)));
						SaveLoadSlot_Reference->SaveCountText->SetText(FText::FromString("#" + FString::FromInt(LoadedSlot->CurrentTotalManualSaveCount)));

						SaveFileScrollBox->AddChild(SaveLoadSlot_Reference);
					}
					else {
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to load Save File information.")));
					}
				}
			}
		}
	}
}


void UBaseClass_Widget_SaveLoad::CloseWidget()
{
	if (PlayerReference) {
		PlayerReference->CurrentOpenMenuWidget->RemoveFromParent();
		PlayerReference->CurrentOpenMenuWidget = NULL;
		PlayerReference->CurrentOpenMenuWidget_Class = NULL;

		if (PauseMenu_Class) {
			PauseMenu_Reference = CreateWidget<UBaseClass_Widget_PauseMenu>(GetWorld(), PauseMenu_Class);
			Cast<UBaseClass_Widget_PauseMenu>(PauseMenu_Reference)->LocalPlayerReference = PlayerReference;
			PauseMenu_Reference->AddToViewport();

			PlayerReference->CurrentOpenMenuWidget = PauseMenu_Reference;
			PlayerReference->CurrentOpenMenuWidget_Class = PauseMenu_Class;
		}
	}
}