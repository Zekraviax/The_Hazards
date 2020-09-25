#include "SubWidget_SaveLoadSlot.h"

#include "SaveFile_Slot.h"
#include "SaveFile_MetaList.h"
#include "Entity_Player.h"
#include "SubWidget_NameSaveFile.h"
#include "SubWidget_WarningAndErrorPrompt.h"
#include "BaseClass_Widget_SaveLoad.h"


void USubWidget_SaveLoadSlot::SetSlotData()
{
	switch (SlotFunction)
	{
	case (E_SaveLoadSlotFunctions::E_SaveNewSlot):
		SlotNameText->SetText(FText::FromString("New Save"));
		SelectButtonText->SetText(FText::FromString("Save"));
		break;
	case (E_SaveLoadSlotFunctions::E_SaveExistingSlot):
		SelectButtonText->SetText(FText::FromString("Save"));
		break;
	case (E_SaveLoadSlotFunctions::E_LoadExistingSLot):
		SelectButtonText->SetText(FText::FromString("Load"));
		break;
	default:
		break;
	}
}


void USubWidget_SaveLoadSlot::SelectSlot()
{
	switch (SlotFunction)
	{
	case (E_SaveLoadSlotFunctions::E_SaveNewSlot):
		if (NameSaveFileWidget_Class) {
			if (NameSaveFileWidget_Reference) {
				NameSaveFileWidget_Reference->RemoveFromParent();
				NameSaveFileWidget_Reference = NULL;
			}

			NameSaveFileWidget_Reference = CreateWidget<USubWidget_NameSaveFile>(GetWorld(), NameSaveFileWidget_Class);
			NameSaveFileWidget_Reference->SaveLoadSlotWidget_Reference = this;
			NameSaveFileWidget_Reference->OpenWidget();
			NameSaveFileWidget_Reference->AddToViewport();
		}
		break;
	case (E_SaveLoadSlotFunctions::E_SaveExistingSlot):
		if (WarningAndErrorPrompt_Class) {
			WarningAndErrorPrompt_Reference = CreateWidget<USubWidget_WarningAndErrorPrompt>(GetWorld(), WarningAndErrorPrompt_Class);
			WarningAndErrorPrompt_Reference->ParentWidget_Reference = this;
			WarningAndErrorPrompt_Reference->SetPromptText(E_WarningAndError_Types::E_OverwriteSaveFile);
			WarningAndErrorPrompt_Reference->ConfirmFunctionEnum = E_WarningAndError_ConfirmButtonFunctions::E_OverwriteSaveFile;
			WarningAndErrorPrompt_Reference->DenyFunctionEnum = E_WarningAndError_DenyButtonFunctions::E_ClosePromptWidget;
			WarningAndErrorPrompt_Reference->AddToViewport();
		}
		break;
	case (E_SaveLoadSlotFunctions::E_LoadExistingSLot):
		if (WarningAndErrorPrompt_Class) {
			WarningAndErrorPrompt_Reference = CreateWidget<USubWidget_WarningAndErrorPrompt>(GetWorld(), WarningAndErrorPrompt_Class);
			WarningAndErrorPrompt_Reference->ParentWidget_Reference = this;
			WarningAndErrorPrompt_Reference->SetPromptText(E_WarningAndError_Types::E_DoubleCheckLoadGame);
			WarningAndErrorPrompt_Reference->ConfirmFunctionEnum = E_WarningAndError_ConfirmButtonFunctions::E_LoadGame;
			WarningAndErrorPrompt_Reference->DenyFunctionEnum = E_WarningAndError_DenyButtonFunctions::E_ClosePromptWidget;
			WarningAndErrorPrompt_Reference->AddToViewport();
		}
		break;
	default:
		break;
	}
}


void USubWidget_SaveLoadSlot::CreateNewSaveFileSlot(FText SaveSlotName)
{
	// Get Player
	AEntity_Player* PlayerPawn = Cast<AEntity_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	USaveFile_MetaList* MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));
	FAsyncSaveGameToSlotDelegate SaveDelegate;

	if (MetaList != nullptr) {
		// Set Slot Variables
		SlotReference = Cast<USaveFile_Slot>(UGameplayStatics::CreateSaveGameObject(USaveFile_Slot::StaticClass()));

		if (SlotReference->IsValidLowLevel()) {
			SlotReference->SaveSlotName = SaveSlotName;
			SlotReference->DateSaved = FDateTime::Now();

			// Get the MetaList in order to increase the TotalManualSave count
			if (MetaList->IsValidLowLevel()) {
				MetaList->TotalManualSaveCount++;
				SlotReference->CurrentTotalManualSaveCount = MetaList->TotalManualSaveCount;

				UGameplayStatics::SaveGameToSlot(MetaList, "MetaList", 0);
			}

			// Set Player Variables
			SlotReference->PlayerReference = PlayerPawn;

			// Set Enemy Variables
			for (TObjectIterator<AEntity_EnemyNPC> Itr; Itr; ++Itr) {
				AEntity_EnemyNPC* FoundEnemy = *Itr;
				SlotReference->EnemyReferencesArray.AddUnique(FoundEnemy);
			}

			// Bind UObject
			SaveDelegate.BindUObject(SlotReference, &USaveFile_Slot::SaveGameDelegateFunction);
			UGameplayStatics::AsyncSaveGameToSlot(SlotReference, SaveSlotName.ToString(), 0, SaveDelegate);
		}
	} else {

	}
}