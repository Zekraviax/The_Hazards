#include "SaveFile_MetaList.h"


void USaveFile_MetaList::SaveGameDelegateFunction(const FString &SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: File %s saved successfully."), *SlotName));
		UE_LOG(LogTemp, Display, TEXT("Message: File %s saved successfully."), *SlotName);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: File %s failed to save."), *SlotName));
		UE_LOG(LogTemp, Warning, TEXT("Error: File %s failed to save."), *SlotName);
	}
}