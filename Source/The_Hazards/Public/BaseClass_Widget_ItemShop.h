#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/ScrollBox.h"
#include "SubWidget_ShopItemListing.h"

#include "BaseClass_Widget_ItemShop.generated.h"

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_ItemShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* ItemListingsScrollBox;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_ShopItemListing> ShopItemListing_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_ShopItemListing* ShopItemListing_Instance;

// ------------------------- Entities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entities")
	AEntity_Base* PlayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entities")
	AEntity_Base* ShopkeeperReference;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void PopulateShop();

	UFUNCTION(BlueprintCallable)
	void OnExit();
};
