#include "BaseClass_Widget_SaveLoad.h"

#include "SaveFile_MetaList.h"
#include "SaveFile_Slot.h"
#include "Entity_Player.h"
#include "Delegates/Delegate.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/AsyncActionHandleSaveGame.h"
#include "SaveGameSystem.h"
#include "Misc/AssertionMacros.h"
#include "TheHazards_GameInstance.h"


void UBaseClass_Widget_SaveLoad::GetSaveFilesPartOne(bool SetSaveMode)
{
	//FAsyncLoadGameFromSlotDelegate LoadDelegate;
	USaveFile_MetaList* MetaList;
	SaveMode = SetSaveMode;

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
	}
	
	/*if (GetWorld()->IsValidLowLevel())
		MetaList = Cast<UTheHazards_GameInstance>(GetWorld()->GetGameInstance())->ReturnMetaList();
	else*/
	MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	if (MetaList == nullptr) {
		MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::CreateSaveGameObject(USaveFile_MetaList::StaticClass()));
		if (UGameplayStatics::SaveGameToSlot(MetaList, "MetaList", 0)) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: MetaList not detected. Creating new MetaList.")));
			UE_LOG(LogTemp, Warning, TEXT("Warning: MetaList not detected. Creating new MetaList."));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: MetaList not detected. Could not create new MetaList.")));
			UE_LOG(LogTemp, Error, TEXT("Error: MetaList not detected. Could not create new MetaList."));
		}
	}

	if (MetaList != NULL) {
		if (MetaList->IsValidLowLevel()) {
			// Only move to part two if the MetaList is loaded
			GetSaveFilesPartTwo();
		}
	}
}


void UBaseClass_Widget_SaveLoad::GetSaveFilesPartTwo()
{
	USaveFile_MetaList* MetaList;

	//MetaList = Cast<UTheHazards_GameInstance>(GetWorld()->GetGameInstance())->ReturnMetaList();
	MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	if (MetaList == nullptr) {
		MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::CreateSaveGameObject(USaveFile_MetaList::StaticClass()));
		if (UGameplayStatics::SaveGameToSlot(MetaList, "MetaList", 0)) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: MetaList not detected. Creating new MetaList.")));
			UE_LOG(LogTemp, Warning, TEXT("Warning: MetaList not detected. Creating new MetaList."));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Could not create MetaList.")));
			UE_LOG(LogTemp, Error, TEXT("Error: Could not create MetaList."));
		}
	}

	if (SaveLoadSlot_Class->IsValidLowLevel()) {
		//Get all existing saves, if any
		if (MetaList->IsValidLowLevel()) {
			if (MetaList->SaveFileAndLevelNames.Num() > 0) {
				USaveFile_Slot* LoadedSlot;
				int SlotNumber = 0;

				//for (int i = 0; i < MetaList->SaveFileAndLevelNames.Num(); i++) {
				for (auto& Name : MetaList->SaveFileAndLevelNames) {
					//Load Save Slots for texts
					LoadedSlot = Cast<USaveFile_Slot>(UGameplayStatics::LoadGameFromSlot(Name.Key, 0));

					SlotNumber++;

					if (LoadedSlot->IsValidLowLevel()) {
						//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Found slot %s"), *Name.Key));
						//UE_LOG(LogTemp, Display, TEXT("Message: Found Slot %s"), *Name.Key);

						SaveLoadSlot_Reference = CreateWidget<USubWidget_SaveLoadSlot>(GetWorld(), SaveLoadSlot_Class);

						if (SaveLoadSlot_Reference->IsValidLowLevel()) {
							if (SaveMode)
								SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_SaveExistingSlot;
							else
								SaveLoadSlot_Reference->SlotFunction = E_SaveLoadSlotFunctions::E_LoadExistingSLot;

							SaveLoadSlot_Reference->SetSlotData();

							//Set Save Slot texts
							SaveLoadSlot_Reference->SlotNameText->SetText(FText::FromString(Name.Key));
							if (LoadedSlot->PlayerReference != NULL) {
								SaveLoadSlot_Reference->CharacterNameText->SetText(FText::FromString(LoadedSlot->PlayerReference->CharacterSheet.Name));
								SaveLoadSlot_Reference->LevelText->SetText(FText::FromString("Level " + FString::FromInt(LoadedSlot->PlayerReference->Level)));
							}
							SaveLoadSlot_Reference->PlaytimeText->SetText(FText::FromString("00:00"));
							SaveLoadSlot_Reference->DateSavedText->SetText(FText::FromString(LoadedSlot->DateSaved.ToString()));
							SaveLoadSlot_Reference->SlotNumberText->SetText(FText::FromString("Slot " + FString::FromInt(SlotNumber)));
							SaveLoadSlot_Reference->SaveCountText->SetText(FText::FromString("#" + FString::FromInt(LoadedSlot->CurrentTotalManualSaveCount)));

							SaveFileScrollBox->AddChild(SaveLoadSlot_Reference);
						}
						else {
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to create Save File Slot widget.")));
							UE_LOG(LogTemp, Error, TEXT("Error: Failed to create Save File Slot widget."));
						}
					}
					else {
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to load Save File %s."), *Name.Key));
						UE_LOG(LogTemp, Error, TEXT("Error: Failed to load Save File %s."), *Name.Key);
					}
				}

				//MetaList = nullptr;
				//FDebug::DumpStackTraceToLog();
			}
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Meta List Error!")));
			//UE_LOG(LogTemp, Error, TEXT("Error: Meta List Error!"));
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