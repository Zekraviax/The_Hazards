#include "SaveFile_MetaList.h"

#include "BaseClass_Widget_SaveLoad.h"


void USaveFile_MetaList::SaveGameDelegateFunction(const FString &SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: MetaList saved successfully.")));
		UE_LOG(LogTemp, Display, TEXT("Message: MetaList saved successfully."));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: MetaList failed to save.")));
		UE_LOG(LogTemp, Error, TEXT("Error: MetaList failed to save."));
	}
}


void USaveFile_MetaList::LoadGameDelegateFunction(const FString & SlotName, const int32 UserIndex, USaveGame* LoadedData)
{
	if (LoadedData->IsValidLowLevel()) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: MetaList loaded successfully.")));
		UE_LOG(LogTemp, Display, TEXT("Message: MetaList loaded successfully."));

		//for (TObjectIterator<UBaseClass_Widget_SaveLoad> Itr; Itr; ++Itr) {
		//	UBaseClass_Widget_SaveLoad* FoundWidget = *Itr;
		//	if (FoundWidget->IsValidLowLevel()) {
		//		if (!FoundWidget->MetaList->IsValidLowLevel())
		//			FoundWidget->MetaList = Cast<USaveFile_MetaList>(LoadedData);

		//		FoundWidget->GetSaveFilesPartTwo();
		//		//break;
		//	}
		//}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to load MetaList.")));
		UE_LOG(LogTemp, Error, TEXT("Error: Failed to load MetaList."));
	}
}