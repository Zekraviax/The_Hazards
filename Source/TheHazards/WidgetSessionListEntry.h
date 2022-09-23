#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OnlineSessionSettings.h"

#include "WidgetSessionListEntry.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetSessionListEntry : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Save the session info so it's easy to pass to other classes
	FOnlineSessionSearchResult Session;

	// The name of the session
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SessionNameText;

	// The host's character name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HostNameText;

	// Button for attempting to join a session
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinSessionButton;

	// Attempt to join a session
	UFUNCTION(BlueprintCallable)
	void JoinSession();
};