// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/Image.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "SubWidget_ItemDrag.generated.h"

// Forward Declarations
class USubWidget_InventorySlot;

UCLASS()
class THE_HAZARDS_API USubWidget_ItemDrag : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UImage* ItemImage;

// ------------------------- Item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	F_Item_BaseStruct ItemStruct;

// ------------------------- Slot Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot")
	USubWidget_InventorySlot* SlotReference;

// ------------------------- Position
	UPROPERTY()
	float MousePosX;

	UPROPERTY()
	float MousePosY;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void SetPosition();

	UFUNCTION()
	void SetImage();
};
