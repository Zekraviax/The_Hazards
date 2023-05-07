#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TheHazardsVariables.h"

#include "WidgetCraftingWindowItemScrollBox.generated.h"



UCLASS()
class THEHAZARDS_API UWidgetCraftingWindowItemScrollBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FItemBase ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;

	UFUNCTION(BlueprintCallable)
	void SetData(FItemBase NewItemData);

	UFUNCTION(BlueprintCallable)
	void OnMouseButtonDownBegin();

	UFUNCTION()
	void OnDragItemBegin();
};
