#pragma once

#include "CoreMinimal.h"
#include "Entity_Base.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BaseClass_Widget_Dialogue.h"
#include "BaseClass_Widget_ItemShop.h"

#include "Entity_NPC.generated.h"


UCLASS()
class THE_HAZARDS_API AEntity_NPC : public AEntity_Base
{
	GENERATED_BODY()

public:
	AEntity_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractBox;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_Dialogue> DialogueWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_Dialogue* DialogueWidget_Instance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_ItemShop> ItemShop_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_ItemShop* ItemShop_Instance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_DialogueBranch> DialogueBranchWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_DialogueBranch* DialogueBranchWidget_Instance;

// ------------------------- Dialogue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<F_Dialogue_Entry> DialogueLines;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 CurrentDialogueIndex;
	
// Functions
// --------------------------------------------------

// ------------------------- Overlap
	//UFUNCTION()
	//void OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerEndOverlap(class AActor* Self, class AActor* OtherActor);

// ------------------------- Player
	UFUNCTION(BlueprintCallable)
	void PlayerInteract(AEntity_Player* PlayerReference);
};
