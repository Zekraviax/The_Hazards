#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

#include "BaseClass_Widget_ItemCraft.generated.h"

// Forward Declarations
class AEntity_Player;
class USubWidget_ItemCraftInventoryItem;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_ItemCraft : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* InventoryScrollBox;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_ItemCraftInventoryItem> ItemCraftInventoryWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_ItemCraftInventoryItem* ItemCraftInventoryWidget_Reference;

// ------------------------- Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	AEntity_Player* PlayerReference;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void GetPlayerInventory();

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void OnMouseUp();
};