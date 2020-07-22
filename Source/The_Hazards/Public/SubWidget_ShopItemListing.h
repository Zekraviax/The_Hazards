#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TheHazards_GameMode.h"

#include "SubWidget_ShopItemListing.generated.h"

// Forward Declarations
class AEntity_Base;
class UBaseClass_Widget_ItemShop;

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
	UTextBlock* PriceText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UButton* BuyButton;

// ------------------------- Item
	UPROPERTY()
	F_Item_BaseStruct ItemData;

	UPROPERTY()
	AEntity_Base* ShopkeeperReference;

	UPROPERTY()
	UBaseClass_Widget_ItemShop* ShopReference;

	UPROPERTY()
	int IndexInShopkeeperInventory;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();
};
