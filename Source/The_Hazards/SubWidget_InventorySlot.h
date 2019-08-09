// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "SubWidget_ItemDrag.h"
#include "BaseClass_Widget_ItemDescription.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

#include "SubWidget_InventorySlot.generated.h"


// ------------------------- Class-specific Enums
UENUM(BlueprintType)
enum class E_InventorySlot_SlotType : uint8
{
	E_StandardSlot,
	E_EquipmentSlot,
	E_QuickUseSlot
};

UCLASS()
class THE_HAZARDS_API USubWidget_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* AmountText;

// ------------------------- Bound variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound variables")
	int32 ItemAmountBind;

// ------------------------- Slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	E_InventorySlot_SlotType SlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	E_InventorySlot_EquipType EquipmentSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	FString SlotDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	int32 InventorySlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot")
	F_Item_BaseStruct ItemStruct;

// ------------------------- ItemDrag Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Widget")
	TSubclassOf<USubWidget_ItemDrag> ItemDrag_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Widget")
	USubWidget_ItemDrag* ItemDrag_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Widget")
	TSubclassOf<UBaseClass_Widget_ItemDescription> ItemDescription_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Widget")
	UBaseClass_Widget_ItemDescription* ItemDescription_Reference;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void UpdateSlot();

	UFUNCTION(BlueprintCallable)
	void OnMouseDown();

	UFUNCTION(BlueprintCallable)
	void OnMouseUp();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin(FVector2D Coordinates);

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();
};