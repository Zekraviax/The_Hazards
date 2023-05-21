#include "WidgetCraftingWindowItemScrollBox.h"


#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"
#include "TheHazardsPlayerController.h"
#include "WidgetCraftingWindowDescription.h"
#include "WidgetCraftingWindowItemSlot.h"
#include "WidgetMenuCraftingWindow.h"


void UWidgetCraftingWindowItemScrollBox::SetData(FItemBase NewItemData)
{
	ItemData = NewItemData;
	Name->SetText(FText::FromString(NewItemData.Name));
}


void UWidgetCraftingWindowItemScrollBox::OnMouseButtonDownBegin()
{
	if (ItemData.ItemType != EItemTypes::None) {
		if (ItemData.ItemType == EItemTypes::Blueprint) {
			// Find the main crafting window widget
			TArray<UUserWidget*> FoundCraftingWindowWidgets;

			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowWidgets, UWidgetMenuCraftingWindow::StaticClass(), false);

			if (FoundCraftingWindowWidgets.Num() > 0) {
				Cast<UWidgetMenuCraftingWindow>(FoundCraftingWindowWidgets[0])->BlueprintSelected(ItemData);
			} else {
				UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemScrollBox / OnClick() / Error: Could not find any CraftingWindow widgets."));
			}
		} else if (ItemData.ItemType == EItemTypes::Part) {
			OnDragItemBegin();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemScrollBox / OnClick() / Error: Item is not a Blueprint or Part."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemScrollBox / OnClick() / Error: Item has the ItemType of Default."));
	}
}


void UWidgetCraftingWindowItemScrollBox::OnDragItemBegin()
{
	// Hide description widgets (?)
	bool HideDescriptionWidgets = true;

	if (HideDescriptionWidgets) {
		TArray<UUserWidget*> FoundDescriptionWidgets;

		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundDescriptionWidgets, UWidgetCraftingWindowDescription::StaticClass(), false);
		if (FoundDescriptionWidgets.Num() > 0) {
			FoundDescriptionWidgets[0]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if (IsValid(WidgetCraftingWindowItemSlotBlueprintClass)) {
		DragItemSlot = CreateWidget<UWidgetCraftingWindowItemSlot>(GetWorld(), WidgetCraftingWindowItemSlotBlueprintClass);

		DragItemSlot->SetVisibility(ESlateVisibility::HitTestInvisible);
		DragItemSlot->SetDesiredSizeInViewport(FVector2D(100.f, 100.f));
		DragItemSlot->FollowCursor = true;

		Cast<ATheHazardsPlayerController>(GetWorld()->GetFirstPlayerController())->CurrentDraggingWidget = DragItemSlot;

		DragItemSlot->AddToViewport();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemScrollBox / OnDragItemBegin() / Error: WidgetCraftingWindowItemScrollBoxWidgetClass is not valid."));
	}
}