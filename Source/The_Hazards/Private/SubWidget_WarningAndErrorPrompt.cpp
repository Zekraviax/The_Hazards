#include "SubWidget_WarningAndErrorPrompt.h"

#include "TheHazards_GameInstance.h"
#include "SubWidget_SaveLoadSlot.h"


void USubWidget_WarningAndErrorPrompt::SetPromptText(E_WarningAndError_Types PromptType)
{
	switch (PromptType)
	{
	case(E_WarningAndError_Types::E_OverwriteSaveFile):
		HeaderText->SetText(FText::FromString("Save File Already Exists"));
		BodyText->SetText(FText::FromString("Are you sure you wish to overwrite this save file?"));
		DenyButtonText->SetText(FText::FromString("No"));
		ConfirmButtonText->SetText(FText::FromString("Yes"));
		break;
	case(E_WarningAndError_Types::E_DoubleCheckLoadGame):
		HeaderText->SetText(FText::FromString("Load File"));
		BodyText->SetText(FText::FromString("Are you sure you wish to load this file?"));
		DenyButtonText->SetText(FText::FromString("No"));
		ConfirmButtonText->SetText(FText::FromString("Yes"));
		break;
	case(E_WarningAndError_Types::E_UnsavedKeybinds):
		HeaderText->SetText(FText::FromString("Warning!"));
		break;
	default:
		break;
	}
}


void USubWidget_WarningAndErrorPrompt::ConfirmButtonSwitchFunction()
{
	USaveFile_Slot* SaveFileSlot;

	switch (ConfirmFunctionEnum)
	{
	case(E_WarningAndError_ConfirmButtonFunctions::E_OverwriteSaveFile):
		break;
	case(E_WarningAndError_ConfirmButtonFunctions::E_LoadGame):
		// Close Widget
		RemoveFromParent();

		// Tell the GameInstance to load the level
		SaveFileSlot = Cast<USubWidget_SaveLoadSlot>(ParentWidget_Reference)->SlotReference;
		//Cast<UTheHazards_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->LoadSaveFile(SaveFileSlot, GetWorld());
		break;
	default:
		break;
	}
}


void USubWidget_WarningAndErrorPrompt::DenyButtonSwitchFunction()
{
	switch (DenyFunctionEnum)
	{
	case(E_WarningAndError_DenyButtonFunctions::E_ClosePromptWidget):
		RemoveFromParent();
		break;
	default:
		break;
	}
}