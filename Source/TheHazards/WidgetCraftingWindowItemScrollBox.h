#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TheHazardsVariables.h"

#include "WidgetCraftingWindowItemScrollBox.generated.h"


class UWidgetCraftingWindowItemSlot;



UCLASS()
class THEHAZARDS_API UWidgetCraftingWindowItemScrollBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FItemBase ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetCraftingWindowItemSlot> WidgetCraftingWindowItemSlotBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetCraftingWindowItemSlot* DragItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;

	UFUNCTION(BlueprintCallable)
	void SetData(FItemBase NewItemData);

	UFUNCTION(BlueprintCallable)
	void OnMouseButtonDownBegin();

	UFUNCTION()
	void OnDragItemBegin();
};
