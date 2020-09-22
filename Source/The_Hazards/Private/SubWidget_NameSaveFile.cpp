#include "SubWidget_NameSaveFile.h"

#include "SubWidget_SaveLoadSlot.h"
#include "SaveFile_MetaList.h"
#include "Entity_Player.h"


void USubWidget_NameSaveFile::OpenWidget()
{
	if (!PlayerReference) {
		for (TObjectIterator<AEntity_Player> Itr; Itr; ++Itr) {
			AEntity_Player *FoundPlayer = *Itr;
			if (FoundPlayer) {
				PlayerReference = FoundPlayer;
				break;
			}
		}
	}

	PlayerReference->LockMenuButtonActions = true;
}


void USubWidget_NameSaveFile::SelectName()
{
	if (SaveLoadSlotWidget_Reference) {
		bool IsNameInUse = false;
		USaveFile_MetaList* MetaList;
		FAsyncSaveGameToSlotDelegate SaveDelegate;

		MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

		if (!MetaList) {
			// If the MetaList doesn't exist, create it here and now
			MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::CreateSaveGameObject(MetaList_Class));
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: MetaList not detected. Creating new MetaList.")));
		}

		// Check if name isn't in use
		if (MetaList->IsValidLowLevel()) {
			if (MetaList->SaveFileNames.Contains(SaveNameEntryBox->GetText().ToString())) {
				IsNameInUse = true;
			}

			// Add name to Meta List if name is not in use
			if (!IsNameInUse) {
				// Save MetaList
				MetaList->SaveFileNames.AddUnique(SaveNameEntryBox->GetText().ToString());
				//UGameplayStatics::AsyncSaveGameToSlot(MetaList, "MetaList", 0, SaveDelegate);

				if (UGameplayStatics::SaveGameToSlot(MetaList, "MetaList", 0))
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: Save Name to MetaList")));
				else
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Could not save Name to MetaList.")));

				SaveLoadSlotWidget_Reference->CreateNewSaveFileSlot(SaveNameEntryBox->GetText());

				for (TObjectIterator<UBaseClass_Widget_SaveLoad> Itr; Itr; ++Itr) {
					UBaseClass_Widget_SaveLoad *FoundWidget = *Itr;
					if (FoundWidget->IsValidLowLevel()) {
						FoundWidget->GetSaveFiles(true);
						break;
					}
				}

				CloseWidget();
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Save File Name is already in use.")));
			}
		}
	}
}


void USubWidget_NameSaveFile::CloseWidget()
{
	if (SaveLoadSlotWidget_Reference) {
		SaveLoadSlotWidget_Reference->NameSaveFileWidget_Reference = NULL;
	}

	if (!PlayerReference) {
		for (TObjectIterator<AEntity_Player> Itr; Itr; ++Itr) {
			AEntity_Player *FoundPlayer = *Itr;
			if (FoundPlayer) {
				PlayerReference = FoundPlayer;
				break;
			}
		}
	}

	PlayerReference->LockMenuButtonActions = false;

	RemoveFromParent();
}