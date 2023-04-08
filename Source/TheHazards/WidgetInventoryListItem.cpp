#include "WidgetInventoryListItem.h"


#include "Blueprint/WidgetBlueprintLibrary.h"
#include "WidgetItemDescription.h"
#include "WidgetItemRightClickMenu.h"


void UWidgetInventoryListItem::OnCursorBeginHover()
{
	// Find any item description widgets
	TArray<UUserWidget*> FoundDescriptionWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundDescriptionWidgets, UWidgetItemDescription::StaticClass(), false);

	if (FoundDescriptionWidgets.Num() > 0) {
		UWidgetItemDescription* FoundDescriptionWidget = Cast<UWidgetItemDescription>(FoundDescriptionWidgets[0]);

		FoundDescriptionWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		// Set description text
		FoundDescriptionWidget->SetDescriptionText(ItemReference);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetInventoryListItem / OnCursorBeginHover() / Error: No ItemDescription widgets could be found."));
	}
}


void UWidgetInventoryListItem::OnCursorEndHover()
{
	// Find any item description widgets
	TArray<UUserWidget*> FoundDescriptionWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundDescriptionWidgets, UWidgetItemDescription::StaticClass(), false);

	if (FoundDescriptionWidgets.Num() > 0) {
		UWidgetItemDescription* FoundDescriptionWidget = Cast<UWidgetItemDescription>(FoundDescriptionWidgets[0]);

		FoundDescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetInventoryListItem / OnCursorEndHover() / Error: No ItemDescription widgets could be found."));
	}
}


void UWidgetInventoryListItem::OnRightClick()
{
	// Find any right click menu widgets
	TArray<UUserWidget*> FoundRightClickMenuWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundRightClickMenuWidgets, UWidgetItemRightClickMenu::StaticClass(), false);

	if (FoundRightClickMenuWidgets.Num() > 0) {
		UWidgetItemRightClickMenu* FoundRightClickMenuWidget = Cast<UWidgetItemRightClickMenu>(FoundRightClickMenuWidgets[0]);

		FoundRightClickMenuWidget->SetVisibility(ESlateVisibility::Visible);
		FoundRightClickMenuWidget->ClickedWidgetInventoryListItem = this;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetInventoryListItem / OnRightClick() / Error: No RightClickMenu widgets could be found."));
	}
}