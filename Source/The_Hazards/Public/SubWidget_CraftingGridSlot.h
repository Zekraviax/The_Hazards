#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "SubWidget_CraftingGridSlot.generated.h"

// Forward Declarations
class USubWidget_ItemDrag;
class UBaseClass_Widget_OnHoverDescription;


UCLASS()
class THE_HAZARDS_API USubWidget_CraftingGridSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	//UTextBlock* ItemName;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_ItemDrag> ItemDrag_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_ItemDrag* ItemDrag_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_OnHoverDescription> ItemDescription_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_OnHoverDescription* ItemDescription_Reference;

// ------------------------- Item
	UPROPERTY()
	F_Item_BaseStruct ItemData;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin(FVector2D ScreenCoordinates);

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();

	UFUNCTION(BlueprintCallable)
	void OnMouseDown();

	UFUNCTION(BlueprintCallable)
	void OnMouseUp();
};
