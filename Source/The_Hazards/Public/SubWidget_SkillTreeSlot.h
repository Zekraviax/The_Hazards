#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "BaseClass_Widget_OnHoverDescription.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

#include "SubWidget_SkillTreeSlot.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_SkillTreeSlot : public UUserWidget
{
	GENERATED_BODY()
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* SkillImage;

// ------------------------- Slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotNumber;

// ------------------------- Slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	F_Skill_Base SkillReference;

// ------------------------- Description Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description Widget")
	TSubclassOf<UBaseClass_Widget_OnHoverDescription> Description_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Description Widget")
	UBaseClass_Widget_OnHoverDescription* Description_Reference;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnMouseHoverBegin(FVector2D Coordinates);

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverEnd();
};
