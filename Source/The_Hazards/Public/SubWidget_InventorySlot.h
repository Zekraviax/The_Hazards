#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "SubWidget_ItemDrag.h"
#include "BaseClass_Widget_OnHoverDescription.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

#include "SubWidget_InventorySlot.generated.h"

// Forward Declarations
class AEntity_Base;


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

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* AmountText;

// ------------------------- Bound Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	int32 ItemAmountBind;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	AEntity_Base* PlayerReference;

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
	TSubclassOf<UBaseClass_Widget_OnHoverDescription> ItemDescription_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Widget")
	UBaseClass_Widget_OnHoverDescription* ItemDescription_Reference;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void UpdateSlot();

	UFUNCTION(BlueprintCallable)
	void OnMouseDown();

	UFUNCTION(BlueprintCallable)
	void OnMouseUp();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin(FVector2D ScreenCoordinates);

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();

	UFUNCTION()
	void Item_TextBind();
};