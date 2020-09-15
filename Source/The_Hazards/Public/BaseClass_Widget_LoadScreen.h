#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

#include "BaseClass_Widget_LoadScreen.generated.h"


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_LoadScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* LoadScreenImage;

// Functions
// --------------------------------------------------

// ------------------------- 
};
