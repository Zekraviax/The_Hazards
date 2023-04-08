#include "WidgetCraftingWindowItemSlot.h"


#include "Blueprint/WidgetBlueprintLibrary.h"
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