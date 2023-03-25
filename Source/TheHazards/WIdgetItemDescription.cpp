#include "WIdgetItemDescription.h"


void UWIdgetItemDescription::SetDescriptionText(FItemBase ItemReference)
{
	Description->SetText(FText::FromString("Name: " + ItemReference.Name));
}