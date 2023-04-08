#include "WidgetMenuCraftingWindow.h"


#include "Blueprint/WidgetBlueprintLibrary.h"
#include "WidgetCraftingWindowDescription.h"
#include "WidgetCraftingWindowItemSlot.h"


void UWidgetMenuCraftingWindow::OnCraftingWindowItemSlotHoverBegin(UWidgetCraftingWindowItemSlot* HoveredItemSlot)
{
	// Find any crafting window description widgets
	TArray<UUserWidget*> FoundCraftingWindowDescriptionWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowDescriptionWidgets, UWidgetCraftingWindowDescription::StaticClass(), false);

	if (FoundCraftingWindowDescriptionWidgets.Num() > 0) {
		if (Cast<UWidgetCraftingWindowDescription>(FoundCraftingWindowDescriptionWidgets[0])) {
			UWidgetCraftingWindowDescription* FoundCraftingWindowDescriptionWidget = Cast<UWidgetCraftingWindowDescription>(FoundCraftingWindowDescriptionWidgets[0]);

			FoundCraftingWindowDescriptionWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			// Set slot text
			//FoundDescriptionWidget->SetDescriptionText(ItemReference);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / OnCraftingWindowItemSlotHoverBegin() / Error: Widget at index 0 in FoundCraftingWindowDescriptionWidgets array is not a UWidgetCraftingWindowDescription."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / OnCraftingWindowItemSlotHoverBegin() / Error: No CraftingWindowDescriptionWidget widgets could be found."));
	}
}


void UWidgetMenuCraftingWindow::OnCraftingWindowItemSlotHoverEnd(UWidgetCraftingWindowItemSlot* HoveredItemSlot)
{
	// Find any crafting window description widgets
	TArray<UUserWidget*> FoundCraftingWindowDescriptionWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowDescriptionWidgets, UWidgetCraftingWindowDescription::StaticClass(), false);

	if (FoundCraftingWindowDescriptionWidgets.Num() > 0) {
		if (Cast<UWidgetCraftingWindowDescription>(FoundCraftingWindowDescriptionWidgets[0])) {
			UWidgetCraftingWindowDescription* FoundCraftingWindowDescriptionWidget = Cast<UWidgetCraftingWindowDescription>(FoundCraftingWindowDescriptionWidgets[0]);

			FoundCraftingWindowDescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / OnCraftingWindowItemSlotHoverEnd() / Error: Widget at index 0 in FoundCraftingWindowDescriptionWidgets array is not a UWidgetCraftingWindowDescription."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / OnCraftingWindowItemSlotHoverEnd() / Error: No CraftingWindowDescriptionWidget widgets could be found."));
	}
}