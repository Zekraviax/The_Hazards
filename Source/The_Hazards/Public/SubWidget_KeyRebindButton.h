#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

#include "SubWidget_KeyRebindButton.generated.h"

// Forward Declarations
class AEntity_Player;
class ABaseClass_PlayerController;
class USubWidget_KeybindsMenu;


UCLASS()
class THE_HAZARDS_API USubWidget_KeyRebindButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* KeyName;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	USubWidget_KeybindsMenu* KeybindsMenuReference;

// ------------------------- Mapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	FName MappingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	bool IsAxisMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	float AxisMappingScale;

// ------------------------- 
	//UInputSettings *Settings

// Functions
// --------------------------------------------------

// ------------------------- Rebind
	UFUNCTION(BlueprintCallable)
	void EnableRebindKeyMode();
};
