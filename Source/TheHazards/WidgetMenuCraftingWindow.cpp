#include "WidgetMenuCraftingWindow.h"


#include "ActorComponentInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/UniformGridSlot.h"
#include "WidgetCraftingWindowDescription.h"
#include "WidgetCraftingWindowItemScrollBox.h"
#include "WidgetCraftingWindowItemSlot.h"
#include "WidgetMenuCraftingWindow.h"


void UWidgetMenuCraftingWindow::PopulateScrollBoxes()
{
	if (OwningEntityInventoryComponent->IsValidLowLevel()) {
		if (CraftingWindowItemScrollBoxClass->IsValidLowLevel()) {
			for (int i = 0; i < OwningEntityInventoryComponent->ItemsList.Num(); i++) {
				if (OwningEntityInventoryComponent->ItemsList[i].ItemType == EItemTypes::Blueprint ||
					OwningEntityInventoryComponent->ItemsList[i].ItemType == EItemTypes::Part) {
					CraftingWindowItemScrollBoxReference = CreateWidget<UWidgetCraftingWindowItemScrollBox>(GetWorld(), CraftingWindowItemScrollBoxClass);

					CraftingWindowItemScrollBoxReference->SetData(OwningEntityInventoryComponent->ItemsList[i]);

					if (OwningEntityInventoryComponent->ItemsList[i].ItemType == EItemTypes::Blueprint) {
						BlueprintsInventoryScrollBox->AddChild(CraftingWindowItemScrollBoxReference);
					} else if (OwningEntityInventoryComponent->ItemsList[i].ItemType == EItemTypes::Part) {
						ComponentsInventoryScrollBox->AddChild(CraftingWindowItemScrollBoxReference);
					} else {
						UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / PopulateScrollBoxes() / Error: Inventory ItemsList at index %d has a non-valid ItemType."), i);
					}
				}
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / PopulateScrollBoxes() / Error: CraftingWindowItemScrollBoxClass is not valid."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / PopulateScrollBoxes() / Error: OwningEntityInventoryComponent is not valid."));
	}
}


void UWidgetMenuCraftingWindow::OnCraftingWindowItemSlotHoverBegin(UWidgetCraftingWindowItemSlot* HoveredItemSlot)
{
	// Find any crafting window description widgets
	TArray<UUserWidget*> FoundCraftingWindowDescriptionWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowDescriptionWidgets, UWidgetCraftingWindowDescription::StaticClass(), false);

	if (FoundCraftingWindowDescriptionWidgets.Num() > 0) {
		if (Cast<UWidgetCraftingWindowDescription>(FoundCraftingWindowDescriptionWidgets[0])) {
			UWidgetCraftingWindowDescription* FoundCraftingWindowDescriptionWidget = Cast<UWidgetCraftingWindowDescription>(FoundCraftingWindowDescriptionWidgets[0]);

			FoundCraftingWindowDescriptionWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			FoundCraftingWindowDescriptionWidget->SetText(HoveredItemSlot->CraftingWindowSlotData);
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


void UWidgetMenuCraftingWindow::BlueprintSelected(FItemBase SelectedBlueprint)
{
	if (SelectedBlueprint.BlueprintData.CraftingWindowSlots.Num() > 0) {
		// Find the main crafting window widget
		TArray<UUserWidget*> FoundCraftingWindowItemSlotWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowItemSlotWidgets, UWidgetCraftingWindowItemSlot::StaticClass(), false);

		for (int i = 0; i < FoundCraftingWindowItemSlotWidgets.Num(); i++) {
			FoundCraftingWindowItemSlotWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
		}

		for (int i = 0; i < FoundCraftingWindowItemSlotWidgets.Num(); i++) {
			UWidgetCraftingWindowItemSlot* FoundItemSlot = Cast<UWidgetCraftingWindowItemSlot>(FoundCraftingWindowItemSlotWidgets[i]);
			UUniformGridSlot* FoundUniformGridItemSlot = Cast<UUniformGridSlot>(FoundItemSlot->Slot);

			for (int j = 0; j < SelectedBlueprint.BlueprintData.CraftingWindowSlots.Num(); j++) {
				if (FoundUniformGridItemSlot->Row == SelectedBlueprint.BlueprintData.CraftingWindowSlots[j].Row &&
					FoundUniformGridItemSlot->Column == SelectedBlueprint.BlueprintData.CraftingWindowSlots[j].Column) {
					FoundItemSlot->SetVisibility(ESlateVisibility::Visible);
					FoundItemSlot->CraftingWindowSlotIndex = j;

					// Set slot's accepted part type
					FoundItemSlot->PartSlot = SelectedBlueprint.BlueprintData.CraftingWindowSlots[j].PartType;
					FoundItemSlot->ItemData = SelectedBlueprint;
					FoundItemSlot->CraftingWindowSlotData = SelectedBlueprint.BlueprintData.CraftingWindowSlots[j];
					break;
				} else {
					// Columns and/or rows do not match
				}
			}
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / BlueprintSelected() / Error: Selected blueprint doesn't have any slots!"));
	}
}