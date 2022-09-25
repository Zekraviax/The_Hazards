#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "OnlineSessionSettings.h"

#include "WidgetMenuFindSessions.generated.h"



UCLASS()
class THEHAZARDS_API UWidgetMenuFindSessions : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Scroll Box for displaying all found sessions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* FoundSessionsScrollBox;

	// Populate the 'found sessions' scroll box
	void PopulateFoundSessionsScrollBox(TArray<FOnlineSessionSearchResult> FoundSessionsArray);

	// Start search for sessions
	UFUNCTION()
	void BeginSearchForSessions();
};