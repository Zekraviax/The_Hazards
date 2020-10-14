#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Components/HorizontalBox.h"

#include "BaseClass_Widget_PlayerHUD.generated.h"

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UScrollBox* StatusEffects_ScrollBox;

// ------------------------- Bound Variables 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerHealth_Current;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerHealth_Maximum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerAura_Current;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerAura_Maximum;

// ------------------------- Player-Related Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	AEntity_Base* PlayerReference;
};
