#pragma once


#include "CoreMinimal.h"
#include "ActorInteractable.h"
#include "ActorInteractableItem.generated.h"


class UActorComponentInventory;


UCLASS()
class THEHAZARDS_API AActorInteractableItem : public AActorInteractable
{
	// A single object that can be added to a players' inventory

	GENERATED_BODY()

	// Holds the object's item data
	UPROPERTY(VisibleDefaultsOnly)
	UActorComponentInventory* Inventory;

	// Get overlapping entities
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Only clear the overlapping entity if that entity is no longer overlapping
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);


public:
	// Constructor
	AActorInteractableItem();

	// Mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	// Implementation of the Interactable interface
	virtual bool OnInteract_Implementation() override;

	// Return entity's mesh
	FORCEINLINE class UStaticMeshComponent* GetMeshComponent() const { return Mesh; }
	// Return entity's InventoryComponent
	FORCEINLINE class UActorComponentInventory* GetInventoryComponent() const { return Inventory; }
};