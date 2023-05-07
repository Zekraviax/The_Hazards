#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TheHazardsVariables.h"

#include "WidgetCraftingWindowDescription.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetCraftingWindowDescription : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Description;

	UFUNCTION()
	void SetText(FCraftingBlueprintSlotData InCraftingWindowSlotData);
};