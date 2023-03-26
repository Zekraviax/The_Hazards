#include "WidgetMenuInventory.h"


#include "ActorComponentInventory.h"
#include "Components/UniformGridSlot.h"
#include "WidgetInventoryListItem.h"


void UWidgetMenuInventory::PopulateUnequippedItemsScrollBox(UActorComponentInventory* Inventory)
{
	if (IsValid(InventoryListItemClass)) {
		for (int i = 0; i <= 11; i++) {
			InventoryListItemReference = CreateWidget<UWidgetInventoryListItem>(GetWorld(), InventoryListItemClass);

			if (Inventory->ItemsList.IsValidIndex(i)) {
				InventoryListItemReference->ItemReference = Inventory->ItemsList[i];
			}

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
	for (int i = 0; i < EquippedInventoryItemsGridPanel->GetAllChildren().Num(); i++) {
		InventoryListItemReference = Cast<UWidgetInventoryListItem>(EquippedInventoryItemsGridPanel->GetChildAt(i));

		if (InventoryListItemReference->ItemSlot == EItemSlotTypes::PrimaryWeapon) {
			InventoryListItemReference->ItemReference = Inventory->EquippedPrimaryWeapon;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuInventory / PopulateUnequippedItemsScrollBox() / Error: InventoryListItem widget does not have a proper ItemSlot."));
		}
	}
}