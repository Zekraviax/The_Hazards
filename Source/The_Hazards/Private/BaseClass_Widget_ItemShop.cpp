#include "BaseClass_Widget_ItemShop.h"


void UBaseClass_Widget_ItemShop::PopulateShop()
{
	if (ShopkeeperReference) {
		for (int i = 0; i < ShopkeeperReference->Inventory.Num(); i++) {
			ShopItemListing_Instance = CreateWidget<USubWidget_ShopItemListing>(GetWorld(), ShopItemListing_Class);

			ShopItemListing_Instance->ItemData = ShopkeeperReference->Inventory[i];
			ShopItemListing_Instance->NameText->SetText(FText::FromString(ShopkeeperReference->Inventory[i].Name));
			ShopItemListing_Instance->AmountText->SetText(FText::FromString(FString::FromInt(ShopkeeperReference->Inventory[i].Amount)));

			ItemListingsScrollBox->AddChild(ShopItemListing_Instance);
		}
	}
}