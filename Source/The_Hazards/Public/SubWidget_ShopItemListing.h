#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "SubWidget_ShopItemListing.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_ShopItemListing : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* AmountText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UButton* BuyButton;

// ------------------------- Item
	UPROPERTY()
	F_Item_BaseStruct ItemData;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();
};
