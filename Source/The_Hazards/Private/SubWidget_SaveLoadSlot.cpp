#include "SubWidget_SaveLoadSlot.h"

#include "SaveFile_Slot.h"


void USubWidget_SaveLoadSlot::SetSlotData()
{
	switch (SlotFunction)
	{
	case (E_SaveLoadSlotFunctions::E_SaveNewSlot):
		SlotNameText->SetText(FText::FromString("New Save"));
		break;
	default:
		break;
	}
}


void USubWidget_SaveLoadSlot::SelectSlot()
{

}