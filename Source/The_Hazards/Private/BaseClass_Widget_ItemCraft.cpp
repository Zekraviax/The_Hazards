#include "BaseClass_Widget_ItemCraft.h"

#include "Entity_Player.h"
#include "SubWidget_ItemCraftInventoryItem.h"
#include "SubWidget_ItemDrag.h"


void UBaseClass_Widget_ItemCraft::GetPlayerInventory()
{
	if (PlayerReference && ItemCraftInventoryWidget_Class) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Items in Player Inventory: %s"), *FString::FromInt(PlayerReference->Inventory.Num())));
		UE_LOG(LogTemp, Display, TEXT("Message: Items in Player Inventory: %s"), *FString::FromInt(PlayerReference->Inventory.Num()));

		for (int i = 0; i < PlayerReference->Inventory.Num(); i++) {
			ItemCraftInventoryWidget_Reference = CreateWidget<USubWidget_ItemCraftInventoryItem>(GetWorld(), ItemCraftInventoryWidget_Class);

			ItemCraftInventoryWidget_Reference->ItemData = PlayerReference->Inventory[i];
			ItemCraftInventoryWidget_Reference->SetData();

			InventoryScrollBox->AddChild(ItemCraftInventoryWidget_Reference);
		}

		ItemCraftInventoryWidget_Reference = NULL;
	}
}


void UBaseClass_Widget_ItemCraft::OnMouseUp()
{
	for (TObjectIterator<USubWidget_ItemDrag> Itr; Itr; ++Itr) {
		USubWidget_ItemDrag* FoundWidget = *Itr;

		FoundWidget->RemoveFromParent();
	}
}