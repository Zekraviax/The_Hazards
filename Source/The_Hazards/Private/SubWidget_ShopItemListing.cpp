#include "SubWidget_ShopItemListing.h"

#include "Entity_Base.h"


void USubWidget_ShopItemListing::OnButtonPressed()
{
	if (ShopReference) {
		if (ShopReference->PlayerReference->Money >= ItemData.Value) {

			// Reduce quantity
			ShopReference->ShopkeeperReference->Inventory[IndexInShopkeeperInventory].Amount--;
			ItemData.Amount--;

			// Delete this if shopkeeper runs out of item
			if (ShopReference->ShopkeeperReference->Inventory[IndexInShopkeeperInventory].Amount <= 0) {
				ShopReference->ShopkeeperReference->Inventory.RemoveAt(IndexInShopkeeperInventory);
				this->RemoveFromParent();
			}

			ShopReference->PlayerReference->AddItemToInventory(ItemData);
			AmountText->SetText(FText::FromString(FString::FromInt(ItemData.Amount)));

			ShopReference->PlayerReference->Money -= ItemData.Value;

			// Add to player inventory
			//bool FoundSameItem = false;

			//for (int i = 0; i < ShopReference->PlayerReference->Inventory.Num() - 1; i++) {
			//	if (ItemData == ShopReference->PlayerReference->Inventory[i]) {
			//		ShopReference->PlayerReference->Inventory[i].Amount++;
			//		FoundSameItem = true;
			//		break;
			//	}
			//}
			//if (!FoundSameItem) {
			//	ShopReference->PlayerReference->Inventory.Add(ItemData);
			//}
		}
	}
}