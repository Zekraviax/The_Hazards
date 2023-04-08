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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPartTypes PartSlot;

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();
};