#include "WidgetMenuInventory.h"


#include "ActorComponentInventory.h"
#include "Components/UniformGridSlot.h"
#include "WidgetInventoryListItem.h"


void UWidgetMenuInventory::PopulateUnequippedItemsScrollBox(UActorComponentInventory* Inventory)
{
	if (IsValid(InventoryListItemClass)) {
		// Don't delete all the children, just overwrite the item data
		//UnequippedInventoryItemsGridPanel->ClearChildren();

		for (int i = UnequippedInventoryItemsGridPanel->GetAllChildren().Num() - 1; i >= 0; i--) {
			UWidgetInventoryListItem* InventorySlot = Cast<UWidgetInventoryListItem>(EquippedInventoryItemsGridPanel->GetChildAt(i));
			if (InventorySlot) {
				UnequippedInventoryItemsGridPanel->RemoveChild(InventorySlot);
			}
		}

		for (int i = 0; i < Inventory->ItemsList.Num(); i++) {
			InventoryListItemReference = CreateWidget<UWidgetInventoryListItem>(GetWorld(), InventoryListItemClass);

			if (Inventory->ItemsList.IsValidIndex(i)) {
				InventoryListItemReference->ItemReference = Inventory->ItemsList[i];
			} else {
				UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuInventory / PopulateUnequippedItemsScrollBox() / Error: Inventory ItemsList at index %d is not valid."), i);
			}

			UUniformGridSlot* GridSlot = UnequippedInventoryItemsGridPanel->AddChildToUniformGrid(InventoryListItemReference, (i / 4), (i % 4));

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
			InventoryListItemReference->ItemReference = Inventory->ReturnEquippedPrimaryWeapon();
		} else if (InventoryListItemReference->ItemSlot == EItemSlotTypes::Body) {
			InventoryListItemReference->ItemReference = Inventory->ReturnEquippedTorsoArmour();
		} else {
			//UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuInventory / PopulateUnequippedItemsScrollBox() / Error: InventoryListItem widget does not have a proper ItemSlotType."));
		}
	}
}


void UWidgetMenuInventory::RefreshOtherSlots(UActorComponentInventory* Inventory)
{
	InventoryListItem_QuickUseItem1->ItemReference = Inventory->ReturnEquippedQuickUseItem();
}


void UWidgetMenuInventory::OnCursorBeginOverItemSlot()
{

}

void UWidgetMenuInventory::OnCursorEndOverItemSlot()
{

}


void UWidgetMenuInventory::SwapItemsBetweenSlots(UWidgetInventoryListItem* ItemSlotOne, UWidgetInventoryListItem* ItemSlotTwo)
{
	FItemBase ItemSlotOneTemporaryCopy = ItemSlotOne->ItemReference;
	FItemBase ItemSlotTwoTemporaryCopy = ItemSlotTwo->ItemReference;

	ItemSlotOne->ItemReference = ItemSlotTwoTemporaryCopy;
	ItemSlotTwo->ItemReference = ItemSlotOneTemporaryCopy;
}