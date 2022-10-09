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
	}

	return true;
}