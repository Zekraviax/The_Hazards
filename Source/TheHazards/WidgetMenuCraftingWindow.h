#pragma once


#include "CoreMinimal.h"

#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"

#include "WidgetMenuCraftingWindow.generated.h"


class UWidgetCraftingWindowItemSlot;


UCLASS()
class THEHAZARDS_API UWidgetMenuCraftingWindow : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* CraftingSlotsGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* ComponentsInventoryScrollBox;

	UFUNCTION()
	void OnCraftingWindowItemSlotHoverBegin(UWidgetCraftingWindowItemSlot* HoveredItemSlot);

	UFUNCTION()
	void OnCraftingWindowItemSlotHoverEnd(UWidgetCraftingWindowItemSlot* HoveredItemSlot);
};
