#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

#include "BaseClass_Widget_SaveLoad.generated.h"


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_SaveLoad : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* SaveFileScrollBox;

// Functions
// --------------------------------------------------

// ------------------------- Save Files
	UFUNCTION()
	void GetSaveFiles(bool SaveMode);
};
