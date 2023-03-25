#pragma once


#include "CoreMinimal.h"

#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "TheHazardsVariables.h"

#include "WIdgetItemDescription.generated.h"


UCLASS()
class THEHAZARDS_API UWIdgetItemDescription : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Description;

	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(FItemBase ItemReference);
};