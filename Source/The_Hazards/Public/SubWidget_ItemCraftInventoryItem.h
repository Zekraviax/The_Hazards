#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/TextBlock.h"

#include "SubWidget_ItemCraftInventoryItem.generated.h"

// Forward Declarations
class USubWidget_ItemDrag;
class UBaseClass_Widget_OnHoverDescription;


UCLASS()
class THE_HAZARDS_API USubWidget_ItemCraftInventoryItem : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemNumberText;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_ItemDrag> ItemDrag_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_ItemDrag* ItemDrag_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_OnHoverDescription> ItemDescription_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_OnHoverDescription* ItemDescription_Reference;

// ------------------------- References
	UPROPERTY()
	F_Item_BaseStruct ItemData;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void SetData();

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin(FVector2D ScreenCoordinates);

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();

	UFUNCTION(BlueprintCallable)
	void OnMouseDown();

	UFUNCTION(BlueprintCallable)
	void OnMouseUp();
};
