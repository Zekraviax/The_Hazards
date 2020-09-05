#include "SaveFile_Slot.h"


void USaveFile_Slot::SaveGameDelegateFunction(const FString &SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess) 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("File %s saved successfully."), *SlotName));
	else 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: File %s failed to save."), *SlotName));
}