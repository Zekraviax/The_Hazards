#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WidgetItemRightClickMenu.generated.h"


// Forward declarations
class UWidgetInventoryListItem;


UCLASS()
class THEHAZARDS_API UWidgetItemRightClickMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EquipButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* UnequipButton;

	UPROPERTY()
	UWidgetInventoryListItem* ClickedWidgetInventoryListItem;

	UFUNCTION(BlueprintCallable)
	void ShowHideEquipUnequipButtons(bool ShowEquipButton);

	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();

	UFUNCTION(BlueprintCallable)
	void UnequipButtonPressed();
};
