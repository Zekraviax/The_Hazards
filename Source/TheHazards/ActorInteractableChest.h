#pragma once


#include "CoreMinimal.h"
#include "ActorInteractable.h"
#include "ActorInteractableChest.generated.h"


class AActorInteractableItem;
class UActorComponentInventory;


UCLASS()
class THEHAZARDS_API AActorInteractableChest : public AActorInteractable
{
	// Chests are objects that will drop items from their inventory when interacted with

	GENERATED_BODY()

	FActorSpawnParameters SpawnInfo;

	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	UActorComponentInventory* Inventory;

public:
	// Constructor
	AActorInteractableChest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActorInteractableItem> InteractableItemBlueprintClass;

	UFUNCTION(BlueprintCallable)
	void OnInteract();
};
