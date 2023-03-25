#include "WidgetMenuInventory.h"


#include "ActorComponentInventory.h"
#include "Components/UniformGridSlot.h"
#include "WidgetInventoryListItem.h"


void UWidgetMenuInventory::PopulateUnequippedItemsScrollBox()
{
	if (IsValid(InventoryListItemClass)) {
		for (int i = 0; i <= 11; i++) {
			InventoryListItemReference = CreateWidget<UWidgetInventoryListItem>(GetWorld(), InventoryListItemClass);
			//InventoryListItemReference->ItemSlot = EItemSlotTypes::Default;

			UUniformGridSlot* GridSlot = UnequippedInventoryItemsGridPanel->AddChildToUniformGrid(InventoryListItemReference, (i % 4), (i / 4));

			GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuInventory / PopulateUnequippedItemsScrollBox() / Error: InventoryListItemClass is not valid."));
	}
}


void UWidgetMenuInventory::PopulateEquippedItemsScrollBox(UActorComponentInventory* Inventory)
{
	//if (IsValid(InventoryListItemClass)) {
	//	for (int i = 0; i <= 11; i++) {
	//		InventoryListItemReference = CreateWidget<UWidgetInventoryListItem>(GetWorld(), InventoryListItemClass);

	//		UUniformGridSlot* GridSlot = EquippedInventoryItemsGridPanel->AddChildToUniformGrid(InventoryListItemReference, (i % 4), (i / 4));

	//		GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	//		GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	//		// Populate pre-determined slot with equipped items
	//		if (i == 0) {
	//			InventoryListItemReference->ItemReference = Inventory->EquippedPrimaryWeapon;
	//		}
	//	}
	//} else {
	//	UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuInventory / PopulateEquippedItemsScrollBox() / Error: InventoryListItemClass is not valid."));
	//}
}