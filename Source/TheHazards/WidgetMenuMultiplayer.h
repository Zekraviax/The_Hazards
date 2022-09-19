#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WidgetMenuMultiplayer.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetMenuMultiplayer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Open the 'Host Session' menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	UButton* OpenHostSessionMenuButton;
};
