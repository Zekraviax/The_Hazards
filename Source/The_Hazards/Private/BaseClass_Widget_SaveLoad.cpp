#include "BaseClass_Widget_SaveLoad.h"

#include "SaveFile_MetaList.h"
#include "SaveFile_Slot.h"
#include "Entity_Player.h"

void UBaseClass_Widget_SaveLoad::GetSaveFiles(bool SaveMode)
{
	FAsyncLoadGameFromSlotDelegate LoadDelegate;

	// Pre-emptively load the Meta List
	USaveFile_MetaList* MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));
	//LoadDelegate.BindUObject(MetaList, MetaList->GetClass().Load);

	if (!MetaList->IsValidLowLevel()) {
		MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::CreateSaveGameObject(USaveFile_MetaList::StaticClass()));
	}

	// Clear the SaveFileScrollBox widget
	if (SaveFileScrollBox->IsValidLowLevel()) {
		if (SaveFileScrollBox->GetChildrenCount() > 0) {
			SaveFileScrollBox->ClearChildren();
		}
	}

	if (SaveLoadSlot_Class->IsValidLowLevel()) {
		// Create New Save widget if SaveMode is true
		if (SaveMode && GetWorld()->IsValidLowLevel()) {
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
		if (MetaList->IsValidLowLevel()) {
			if (MetaList->SaveFileNames.Num() > 0) {
				USaveFile_Slot* LoadedSlot;

				for (int i = 0; i < MetaList->SaveFileNames.Num(); i++) {
					// Load Save Slots for texts
					LoadedSlot = Cast<USaveFile_Slot>(UGameplayStatics::LoadGameFromSlot(MetaList->SaveFileNames[i], 0));

					if (LoadedSlot->IsValidLowLevel()) {
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Found slot %s"), *MetaList->SaveFileNames[i]));
						UE_LOG(LogTemp, Display, TEXT("Message: Found Slot %s"), *MetaList->SaveFileNames[i]);

						SaveLoadSlot_Reference = CreateWidget<USubWidget_SaveLoadSlot>(GetWorld(), SaveLoadSlot_Class);

						if (SaveLoadSlot_Reference->IsValidLowLevel()) {
							if (SaveMode)
								SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_SaveExistingSlot;
							else
								SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_LoadExistingSLot;

							SaveLoadSlot_Reference->SetSlotData();

							// Set Save Slot texts
							SaveLoadSlot_Reference->SlotNameText->SetText(FText::FromString(MetaList->SaveFileNames[i]));
							SaveLoadSlot_Reference->CharacterNameText->SetText(FText::FromString(LoadedSlot->PlayerReference->CharacterSheet.Name));
							//SaveLoadSlot_Reference->LevelText->SetText(FText::FromString("Level " + FString::FromInt(LoadedSlot->PlayerReference->Level)));
							//SaveLoadSlot_Reference->PlaytimeText->SetText(FText::FromString("00:00"));
							//SaveLoadSlot_Reference->DateSavedText->SetText(FText::FromString(LoadedSlot->DateSaved.ToString()));
							//SaveLoadSlot_Reference->SlotNumberText->SetText(FText::FromString("Slot " + FString::FromInt(i)));
							//SaveLoadSlot_Reference->SaveCountText->SetText(FText::FromString("#" + FString::FromInt(LoadedSlot->CurrentTotalManualSaveCount)));

							SaveFileScrollBox->AddChild(SaveLoadSlot_Reference);
						} else {
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to create Save File Slot widget.")));
							UE_LOG(LogTemp, Warning, TEXT("Error: Failed to create Save File Slot widget."));
						}
					}
					else {
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to load Save File %s."), *MetaList->SaveFileNames[i]));
						UE_LOG(LogTemp, Warning, TEXT("Error: Failed to load Save File %s."), *MetaList->SaveFileNames[i]);
					}
				}
			}
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Meta List Error!")));
			UE_LOG(LogTemp, Warning, TEXT("Error: Meta List Error!"));
		}
	}
}


void UBaseClass_Widget_SaveLoad::CloseWidget()
{
	// Unload the MetaList?

	if (!Player_Controller_Reference && GetWorld()) {
		Player_Controller_Reference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}

	if (Player_Controller_Reference) {
		Player_Controller_Reference->CurrentOpenMenuWidget->RemoveFromParent();
		Player_Controller_Reference->CurrentOpenMenuWidget = NULL;
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = NULL;
	}

	if (PauseMenu_Class) {
		if (!Player_Controller_Reference->MainMenuMode) {
			PauseMenu_Reference = CreateWidget<UBaseClass_Widget_PauseMenu>(GetWorld(), PauseMenu_Class);
			Cast<UBaseClass_Widget_PauseMenu>(PauseMenu_Reference)->LocalPlayerReference = PlayerReference;
			PauseMenu_Reference->AddToViewport();

			Player_Controller_Reference->CurrentOpenMenuWidget = PauseMenu_Reference;
			Player_Controller_Reference->CurrentOpenMenuWidget_Class = PauseMenu_Class;
		} else {
			//MainMenu_Reference = CreateWidget<UBaseClass_Widget_MainMenu>(GetWorld(), MainMenu_Class);
			////Cast<UBaseClass_Widget_MainMenu>(MainMenu_Reference)->LocalPlayerReference = PlayerReference;
			////MainMenu_Reference->AddToViewport();

			//Player_Controller_Reference->CurrentOpenMenuWidget = MainMenu_Reference;
			//Player_Controller_Reference->CurrentOpenMenuWidget_Class = MainMenu_Class;
		}
	}
}