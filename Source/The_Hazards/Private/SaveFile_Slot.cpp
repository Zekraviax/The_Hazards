#include "SaveFile_Slot.h"

#include "BaseClass_Widget_SaveLoad.h"
#include "SubWidget_SaveLoadSlot.h"
#include "Thehazards_GameInstance.h"


void USaveFile_Slot::SaveGameDelegateFunction(const FString &SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: File %s saved successfully."), *SlotName));
		UE_LOG(LogTemp, Display, TEXT("Message: File %s saved successfully."), *SlotName);

		// Refresh save file slots list
		for (TObjectIterator<UBaseClass_Widget_SaveLoad> Itr; Itr; ++Itr) {
			UBaseClass_Widget_SaveLoad *FoundWidget = *Itr;

			if (FoundWidget->IsValidLowLevel() && FoundWidget->IsInViewport()) {
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: Found SaveLoad Widget in Viewport")));
				UE_LOG(LogTemp, Display, TEXT("Message: Found SaveLoad Widget in Viewport"));
				FoundWidget->GetSaveFilesPartOne(true);
				break;
			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: File %s failed to save."), *SlotName));
		UE_LOG(LogTemp, Error, TEXT("Error: File %s failed to save."), *SlotName);
	}
}


void USaveFile_Slot::LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	if (LoadedGameData != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: File %s loaded successfully."), *SlotName));
		UE_LOG(LogTemp, Display, TEXT("Message: File %s loaded successfully."), *SlotName);

		if (GameInstanceReference) {
			GameInstanceReference->LoadSaveFilePartThree();
		}
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: File %s failed to load."), *SlotName));
		UE_LOG(LogTemp, Error, TEXT("Error: File %s failed to load."), *SlotName);
	}
}