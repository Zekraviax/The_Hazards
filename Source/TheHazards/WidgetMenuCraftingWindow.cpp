#include "WidgetMenuCraftingWindow.h"


#include "ActorComponentInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/UniformGridSlot.h"
#include "EntityBaseCharacter.h"
#include "TheHazardsPlayerController.h"
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
			FoundCraftingWindowDescriptionWidget->SetText(HoveredItemSlot->CraftingWindowSlotData, HoveredItemSlot->ItemData);
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
		for (int i = 0; i < CraftingSlotsGridPanel->GetChildrenCount(); i++) {
			if (Cast<UWidgetCraftingWindowItemSlot>(CraftingSlotsGridPanel->GetChildAt(i))) {
				CraftingSlotsGridPanel->GetChildAt(i)->SetVisibility(ESlateVisibility::Hidden);
			}
		}

		TArray<UUserWidget*> FoundCraftingWindowItemSlotWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowItemSlotWidgets, UWidgetCraftingWindowItemSlot::StaticClass(), false);

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
					//FoundItemSlot->ItemData = SelectedBlueprint;
					FoundItemSlot->CraftingWindowSlotData = SelectedBlueprint.BlueprintData.CraftingWindowSlots[j];
					break;
				} else {
					// Columns and/or rows do not match
				}
			}
		}

		CurrentSelectedBlueprint = SelectedBlueprint;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetMenuCraftingWindow / BlueprintSelected() / Error: Selected blueprint doesn't have any slots!"));
	}
}


bool UWidgetMenuCraftingWindow::ItemCraftingCheck()
{
	bool CanCraftItem = true;
	TArray<UUserWidget*> FoundCraftingWindowItemSlotWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowItemSlotWidgets, UWidgetCraftingWindowItemSlot::StaticClass(), false);

	for (int i = 0; i < FoundCraftingWindowItemSlotWidgets.Num(); i++) {
		UWidgetCraftingWindowItemSlot* FoundSlot = Cast<UWidgetCraftingWindowItemSlot>(FoundCraftingWindowItemSlotWidgets[i]);
		if (FoundSlot) {
			if (FoundSlot->Visibility == ESlateVisibility::Visible) {
				FString SlotPartTypeString = UEnum::GetValueAsString(FoundSlot->PartSlot);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UWidgetMenuCraftingWindow / ItemCraftingCheck / Part Missing: %s"), *SlotPartTypeString));

				// Does this slot have a crafting component that is listed on the blueprint?
				if (FoundSlot->ItemData.PartData.PartType == EPartTypes::None) {
					CanCraftItem = false;

					// Break out of the for loop if even one slot returns false, because that means the item is missing at least one necessary part to craft it
					//break;
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UWidgetMenuCraftingWindow / ItemCraftingCheck / Can Item Be Crafted: %s"), CanCraftItem ? TEXT("True") : TEXT("False")));
	return CanCraftItem;
}


void UWidgetMenuCraftingWindow::CraftItem()
{
	TArray<FItemBase> PartsUsed;

	// Find all the parts in the player's inventory and delete them
	TArray<UUserWidget*> FoundCraftingWindowItemSlotWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundCraftingWindowItemSlotWidgets, UWidgetCraftingWindowItemSlot::StaticClass(), false);

	for (int i = 0; i < FoundCraftingWindowItemSlotWidgets.Num(); i++) {
		UWidgetCraftingWindowItemSlot* FoundSlot = Cast<UWidgetCraftingWindowItemSlot>(FoundCraftingWindowItemSlotWidgets[i]);
		if (FoundSlot) {
			if (FoundSlot->Visibility == ESlateVisibility::Visible) {
				PartsUsed.Add(FoundSlot->ItemData);
			}
		}
	}

	// Create weapon based on the parts used
	FItemBase CraftedItem;
	CraftedItem.ItemType = CurrentSelectedBlueprint.BlueprintData.CraftedItemType;
	CraftedItem.Name = "Crafted Item";

	// Switch based on item types
	if (CurrentSelectedBlueprint.BlueprintData.CraftedItemType == EItemTypes::Weapon) {
		CraftedItem.WeaponData.WeaponType = CurrentSelectedBlueprint.BlueprintData.WeaponType;

		// For weapons, get all the component parts and add their stats together
		for (int i = 0; i < PartsUsed.Num(); i++) {
			CraftedItem.WeaponData.DamagePerShot += PartsUsed[i].WeaponData.DamagePerShot;
		}
	}
	
	UActorComponentInventory* PlayerInventory = Cast<ATheHazardsPlayerController>(GetWorld()->GetFirstPlayerController())->GetPawnAsEntityBaseCharacter()->GetInventoryComponent();
	PlayerInventory->ItemsList.Add(CraftedItem);

	// Delete the parts used from the player's inventory
	for (int i = 0; i < PartsUsed.Num(); i++) {
		PlayerInventory->ItemsList.Remove(PartsUsed[i]);
	}
}