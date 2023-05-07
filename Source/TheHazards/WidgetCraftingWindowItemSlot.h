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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool FollowCursor = false;

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();

	UFUNCTION(BlueprintCallable)
	void OnMouseButtonDownBegin();
};