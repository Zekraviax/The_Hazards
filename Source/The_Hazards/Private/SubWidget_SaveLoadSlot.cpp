#include "SubWidget_SaveLoadSlot.h"

#include "SaveFile_Slot.h"
#include "SaveFile_MetaList.h"
#include "Entity_Player.h"
#include "SubWidget_NameSaveFile.h"
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

		break;
	case (E_SaveLoadSlotFunctions::E_LoadExistingSLot):

		break;
	default:
		break;
	}
}


void USubWidget_SaveLoadSlot::CreateNewSaveFileSlot(FText SaveSlotName)
{
	if (SlotClass) {
		// Get Player
		AEntity_Player* PlayerPawn = Cast<AEntity_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		FAsyncSaveGameToSlotDelegate SaveDelegate;

		// Set Slot Variables
		SlotReference = Cast<USaveFile_Slot>(UGameplayStatics::CreateSaveGameObject(SlotClass));
		SlotReference->SaveSlotName = SaveSlotName;
		SlotReference->DateSaved = FDateTime::Now();

		// Get the MetaList in order to increase the TotalManualSave count
		if (USaveFile_MetaList* MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0))) {
			MetaList->TotalManualSaveCount++;
			SlotReference->CurrentTotalManualSaveCount = MetaList->TotalManualSaveCount;
			UGameplayStatics::SaveGameToSlot(MetaList, "MetaList", 0);
		}

		SaveDelegate.BindUObject(SlotReference, &USaveFile_Slot::SaveGameDelegateFunction);

		// Set Player Variables
		SlotReference->PlayerReference = PlayerPawn;

		// Set Enemy Variables
		for (TObjectIterator<AEntity_EnemyNPC> Itr; Itr; ++Itr) {
			AEntity_EnemyNPC* FoundEnemy = *Itr;
			SlotReference->EnemyReferencesArray.AddUnique(FoundEnemy);
		}

		UGameplayStatics::AsyncSaveGameToSlot(SlotReference, SaveSlotName.ToString(), 0, SaveDelegate);

		// Refresh save file slots list
		for (TObjectIterator<UBaseClass_Widget_SaveLoad> Itr; Itr; ++Itr) {
			UBaseClass_Widget_SaveLoad *FoundWidget = *Itr;

			if (FoundWidget) {
				FoundWidget->GetSaveFiles(true);
				//break;
			}
		}
	}
}