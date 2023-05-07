#include "ActorInteractableItem.h"


#include "ActorComponentInventory.h"
#include "EntityBaseCharacter.h"


AActorInteractableItem::AActorInteractableItem()
{
	Inventory = CreateDefaultSubobject<UActorComponentInventory>(TEXT("Inventory"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	InteractBounds->SetupAttachment(Mesh);

	InteractBounds->OnComponentBeginOverlap.AddDynamic(this, &AActorInteractableItem::OnBeginOverlap);
	InteractBounds->OnComponentEndOverlap.AddDynamic(this, &AActorInteractableItem::OnEndOverlap);
}


void AActorInteractableItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<AEntityBaseCharacter>(OtherActor)) {
		OverlappingEntity = Cast<AEntityBaseCharacter>(OtherActor);
	}
}


void AActorInteractableItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappingEntity) {
		OverlappingEntity = NULL;
	}
}


bool AActorInteractableItem::OnInteract_Implementation()
{
	if (Inventory && OverlappingEntity) {
		Destroy();

		OverlappingEntity->GetInventoryComponent()->ItemsList.Add(Inventory->ItemsList[0]);

		UE_LOG(LogTemp, Warning, TEXT("AActorInteractableItem / OnInteract() / Message: Item %s added to player's inventory."), *Inventory->ItemsList[0].Name);

		for (int i = 0; i < OverlappingEntity->GetInventoryComponent()->ItemsList.Num(); i++) {
			UE_LOG(LogTemp, Warning, TEXT("AActorInteractableItem / OnInteract() / Message: Found item %s in player's inventory at index %d."), *OverlappingEntity->GetInventoryComponent()->ItemsList[i].Name, i);
		}
	} else if (!Inventory && OverlappingEntity) {
		UE_LOG(LogTemp, Warning, TEXT("AActorInteractableItem / OnInteract() / Error: Inventory component is not valid."));
	} else if (Inventory && !OverlappingEntity) {
		UE_LOG(LogTemp, Warning, TEXT("AActorInteractableItem / OnInteract() / Error: OverlappingEntity is not valid."));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AActorInteractableItem / OnInteract() / Error: Both Inventory component and OverlappingEntity are not valid."));
	}

	return true;
}