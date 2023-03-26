#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"

#include "WidgetMenuInventory.generated.h"


class UActorComponentInventory;
class UWidgetInventoryListItem;


UCLASS()
class THEHAZARDS_API UWidgetMenuInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* UnequippedInventoryItemsGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* EquippedInventoryItemsGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetInventoryListItem> InventoryListItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetInventoryListItem* InventoryListItemReference;

	UFUNCTION(BlueprintCallable)
	void PopulateUnequippedItemsScrollBox(UActorComponentInventory* Inventory);

	UFUNCTION(BlueprintCallable)
	void PopulateEquippedItemsScrollBox(UActorComponentInventory* Inventory);
};
