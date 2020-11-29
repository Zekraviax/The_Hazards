#include "SubWidget_NameSaveFile.h"

#include "SubWidget_SaveLoadSlot.h"
#include "SaveFile_MetaList.h"
#include "Entity_Player.h"
#include "TheHazards_GameInstance.h"


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
		FAsyncSaveGameToSlotDelegate SaveDelegate;
		USaveFile_MetaList* MetaList;

		MetaList = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

		if (MetaList == nullptr) {
			// If the MetaList doesn't exist, create it here and now
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

		// Check if name isn't in use
		if (MetaList->IsValidLowLevel()) {
			if (MetaList->SaveFileAndLevelNames.Contains(SaveNameEntryBox->GetText().ToString())) {
				IsNameInUse = true;
			}

			// Add name to Meta List if name is not in use
			if (!IsNameInUse) {
				// Save MetaList
				MetaList->SaveFileNames.AddUnique(SaveNameEntryBox->GetText().ToString());
				MetaList->SaveFileAndLevelNames.Add(SaveNameEntryBox->GetText().ToString(), GetWorld()->GetName());

				if (UGameplayStatics::SaveGameToSlot(MetaList, "MetaList", 0)) {
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: Save Name to MetaList")));
					UE_LOG(LogTemp, Display, TEXT("Message: Save Name to MetaList"));
				} else {
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Could not save Name to MetaList.")));
					UE_LOG(LogTemp, Error, TEXT("Error: Could not save Name to MetaList."));
				}

				SaveLoadSlotWidget_Reference->CreateNewSaveFileSlot(SaveNameEntryBox->GetText());

				//CloseWidget();
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Save File Name %s is already in use."), *SaveNameEntryBox->GetText().ToString()));
				UE_LOG(LogTemp, Error, TEXT("Error: Save File Name %s is already in use."), *SaveNameEntryBox->GetText().ToString());
			}
		}
	}
}


void USubWidget_NameSaveFile::CloseWidget()
{
	if (!PlayerReference) {
		for (TObjectIterator<AEntity_Player> Itr; Itr; ++Itr) {
			AEntity_Player *FoundPlayer = *Itr;
			if (FoundPlayer) {
				PlayerReference = FoundPlayer;
				PlayerReference->LockMenuButtonActions = false;
				break;
			}
		}
	}

	//if (MetaList)
	//	MetaList = nullptr;

	RemoveFromParent();
}