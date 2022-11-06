#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"

#include "WidgetMenuInventory.generated.h"


class UWidgetInventoryListItem;


UCLASS()
class THEHAZARDS_API UWidgetMenuInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Scroll Box for displaying all items that aren't equipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* UnequippedItemsScrollBox;

	UFUNCTION(BlueprintCallable)
	void PopulateUnequippedItemsScrollBox();
};
