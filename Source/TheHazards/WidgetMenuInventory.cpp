#include "WidgetMenuInventory.h"


#include "Components/UniformGridSlot.h"
#include "WidgetInventoryListItem.h"


void UWidgetMenuInventory::PopulateUnequippedItemsScrollBox()
{
	if (IsValid(InventoryListItemClass)) {
		for (int i = 0; i <= 11; i++) {
			InventoryListItemReference = CreateWidget<UWidgetInventoryListItem>(GetWorld(), InventoryListItemClass);

			UUniformGridSlot* GridSlot = InventoryItemsGridPanel->AddChildToUniformGrid(InventoryListItemReference, (i % 4), (i / 4));

			GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
	}
}