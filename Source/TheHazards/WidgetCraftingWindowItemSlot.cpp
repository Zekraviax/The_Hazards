#include "WidgetCraftingWindowItemSlot.h"


#include "Blueprint/WidgetBlueprintLibrary.h"
#include "WidgetCraftingWindowDescription.h"
#include "WidgetCraftingWindowItemSlot.h"
#include "WidgetMenuCraftingWindow.h"


void UWidgetCraftingWindowItemSlot::OnMouseHoverBegin()
{
	// Find the CraftingWindow widget
	// The CraftingWindow widget will handle these functions in order to 
	// avoid having multiple CraftingWindowItemSlots on screen with duplicate code
	TArray<UUserWidget*> FoundCraftingWindowWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowWidgets, UWidgetMenuCraftingWindow::StaticClass(), false);

	if (FoundCraftingWindowWidgets.Num() > 0) {
		if (Cast<UWidgetMenuCraftingWindow>(FoundCraftingWindowWidgets[0])) {
			Cast<UWidgetMenuCraftingWindow>(FoundCraftingWindowWidgets[0])->OnCraftingWindowItemSlotHoverBegin(this);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemSlot / OnMouseHoverEnd() / Error: Widget at index 0 in FoundCraftingWindowWidgets array is not a UWidgetMenuCraftingWindow."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemSlot / OnMouseHoverEnd() / Error: Could not find any UWidgetMenuCraftingWindow widgets."));
	}
}


void UWidgetCraftingWindowItemSlot::OnMouseHoverEnd()
{
	// Find the CraftingWindow widget
	// The CraftingWindow widget will handle these functions in order to 
	// avoid having multiple CraftingWindowItemSlots on screen with duplicate code
	TArray<UUserWidget*> FoundCraftingWindowWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowWidgets, UWidgetMenuCraftingWindow::StaticClass(), false);

	if (FoundCraftingWindowWidgets.Num() > 0) {
		if (Cast<UWidgetMenuCraftingWindow>(FoundCraftingWindowWidgets[0])) {
			Cast<UWidgetMenuCraftingWindow>(FoundCraftingWindowWidgets[0])->OnCraftingWindowItemSlotHoverEnd(this);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemSlot / OnMouseHoverEnd() / Error: Widget at index 0 in FoundCraftingWindowWidgets array is not a UWidgetMenuCraftingWindow."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetCraftingWindowItemSlot / OnMouseHoverEnd() / Error: Could not find any UWidgetMenuCraftingWindow widgets."));
	}
}


void UWidgetCraftingWindowItemSlot::OnMouseButtonDownBegin()
{
	if (ItemData.ItemType != EItemTypes::Default) {
		// Hide description widgets
		TArray<UUserWidget*> FoundDescriptionWidgets;

		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundDescriptionWidgets, UWidgetCraftingWindowDescription::StaticClass(), false);
		if (FoundDescriptionWidgets.Num() > 0) {
			FoundDescriptionWidgets[0]->SetVisibility(ESlateVisibility::Collapsed);
		}

		// Create a clone of this widget that follows the player's mouse cursor
		UWidgetCraftingWindowItemSlot* DragItemSlot = CreateWidget<UWidgetCraftingWindowItemSlot>(GetWorld(), this->GetClass());
		DragItemSlot->FollowCursor = true;
		DragItemSlot->AddToViewport();
		
	} else {
		// ItemType is default, which means there should be no item in this slot
	}
}