#include "SubWidget_ItemDrag.h"

#include "SubWidget_InventorySlot.h"


void USubWidget_ItemDrag::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
}

void USubWidget_ItemDrag::SetImage()
{
	if (ItemStruct.InventoryImage) {
		ItemImage->SetBrushFromTexture(ItemStruct.InventoryImage, true);
	}
}

void USubWidget_ItemDrag::SetPosition() 
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePosX, MousePosY);
	SetPositionInViewport(FVector2D(MousePosX + 50, MousePosY + 50), true);
}