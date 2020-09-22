#include "SaveFile_Slot.h"

#include "BaseClass_Widget_SaveLoad.h"


void USaveFile_Slot::SaveGameDelegateFunction(const FString &SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: File %s saved successfully."), *SlotName));
		UE_LOG(LogTemp, Display, TEXT("Message: File %s saved successfully."), *SlotName);

		// Refresh save file slots list
		for (TObjectIterator<UBaseClass_Widget_SaveLoad> Itr; Itr; ++Itr) {
			UBaseClass_Widget_SaveLoad *FoundWidget = *Itr;

			if (FoundWidget->IsValidLowLevel()) {
				FoundWidget->GetSaveFiles(true);
				//FoundWidget->RemoveFromParent();
				//break;
			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: File %s failed to save."), *SlotName));
		UE_LOG(LogTemp, Warning, TEXT("Error: File %s failed to save."), *SlotName);
	}
}