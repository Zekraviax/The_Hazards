#include "SubWidget_ItemCraftInventoryItem.h"

#include "SubWidget_ItemDrag.h"
#include "BaseClass_Widget_OnHoverDescription.h"


void USubWidget_ItemCraftInventoryItem::SetData()
{
	ItemNameText->SetText(FText::FromString(ItemData.Name));
	ItemNumberText->SetText(FText::FromString(FString::FromInt(ItemData.Amount)));
}


void USubWidget_ItemCraftInventoryItem::OnMouseHoverBegin(FVector2D ScreenCoordinates)
{
	if (ItemDescription_Class) {
		float PosX, PosY, ViewportScaledValueX, ViewportScaledValueY = 0;
		int32 ViewportSizeX, ViewportSizeY;

		ItemDescription_Reference = CreateWidget<UBaseClass_Widget_OnHoverDescription>(GetWorld(), ItemDescription_Class);

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(ViewportSizeX, ViewportSizeY);
		ViewportScaledValueX = (1920 / ViewportSizeX);
		ViewportScaledValueY = (1080 / ViewportSizeY);

		PosX = (ScreenCoordinates.X * ViewportScaledValueX) + 575;
		PosY = (ScreenCoordinates.Y * ViewportScaledValueY) + 100;

		//if (PosY > 405)
		//	PosY = 405;

		ItemDescription_Reference->SetPositionInViewport(FVector2D(PosX, PosY), false);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Widget Position On Screen: %s"), *FVector2D(PosX, PosY).ToString()));
		UE_LOG(LogTemp, Display, TEXT("Message: Widget Position On Screen: %s"), *FVector2D(PosX, PosY).ToString());
		ItemDescription_Reference->AddToViewport();
	}
}


void USubWidget_ItemCraftInventoryItem::OnMouseHoverEnd()
{
	if (ItemDescription_Reference) {
		ItemDescription_Reference->RemoveFromParent();
		ItemDescription_Reference = NULL;
	}
}


void USubWidget_ItemCraftInventoryItem::OnMouseDown()
{
	if (ItemDrag_Class) {
		ItemDrag_Reference = CreateWidget<USubWidget_ItemDrag>(GetWorld(), ItemDrag_Class);
		//ItemDrag_Reference->SlotReference = this;
		ItemDrag_Reference->ItemStruct = ItemData;
		ItemDrag_Reference->SetImage();
		ItemDrag_Reference->AddToViewport();

		//ItemImage->SetBrushFromTexture(NULL, true);
	}
}


void USubWidget_ItemCraftInventoryItem::OnMouseUp()
{
	//for (TObjectIterator<USubWidget_ItemDrag> Itr; Itr; ++Itr) {
	//	USubWidget_ItemDrag* FoundWidget = *Itr;

	//	FoundWidget->RemoveFromParent();
	//}
}