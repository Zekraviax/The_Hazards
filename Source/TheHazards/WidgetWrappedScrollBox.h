#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"

#include "WidgetWrappedScrollBox.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetWrappedScrollBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* WrappedScrollBox;
};