#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "TheHazardsVariables.h"

#include "WidgetInventoryListItem.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetInventoryListItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FItemBase ItemReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemSlotTypes ItemSlot = EItemSlotTypes::Default;

	UFUNCTION(BlueprintCallable)
	void OnCursorBeginHover();

	UFUNCTION(BlueprintCallable)
	void OnCursorEndHover();

	UFUNCTION(BlueprintCallable)
	void OnRightClick();
};
