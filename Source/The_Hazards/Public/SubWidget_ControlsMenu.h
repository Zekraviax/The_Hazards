#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

#include "SubWidget_ControlsMenu.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_ControlsMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	// Mouse Sensitivity

// Functions
// --------------------------------------------------

// ------------------------- 
};
