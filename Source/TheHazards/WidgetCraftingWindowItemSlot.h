#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "TheHazardsVariables.h"

#include "WidgetCraftingWindowItemSlot.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetCraftingWindowItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FItemBase ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FCraftingBlueprintSlotData CraftingWindowSlotData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CraftingWindowSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPartTypes PartSlot;

	// Is the widget being dragged by the player?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool FollowCursor = false;

	// WHen a player starts dragging a widget, this is the widget they clicked on
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* AttachedWidget;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();

	UFUNCTION(BlueprintCallable)
	void OnMouseButtonDownBegin();

	UFUNCTION(BlueprintCallable)
	void OnMouseButtonUpBegin(UWidgetCraftingWindowItemSlot* DraggedWidget);
};