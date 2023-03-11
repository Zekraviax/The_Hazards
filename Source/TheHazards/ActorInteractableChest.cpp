#include "ActorInteractableChest.h"


#include "ActorInteractableItem.h"
#include "ActorComponentInventory.h"


AActorInteractableChest::AActorInteractableChest()
{
	Inventory = CreateDefaultSubobject<UActorComponentInventory>(TEXT("Inventory"));
}


void AActorInteractableChest::OnInteract()
{
	if (Inventory && InteractableItemBlueprintClass) {
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		for (FItemBase Item : Inventory->ItemsList) {
			FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 2.5f);

			AActorInteractableItem* ItemObject = GetWorld()->SpawnActor<AActorInteractableItem>(InteractableItemBlueprintClass, SpawnLocation, GetActorRotation(), SpawnInfo);
			ItemObject->GetInventoryComponent()->ItemsList.Add(Item);

			FVector Location = ItemObject->GetActorLocation();

			float LaunchX = FMath::RandRange(GetActorLocation().X - 1000.f, GetActorLocation().X + 1000.f);
			float LaunchY = FMath::RandRange(GetActorLocation().Y - 1000.f, GetActorLocation().Y + 1000.f);
			float LaunchZ = 500.f;

			ItemObject->GetMeshComponent()->AddImpulse(FVector(LaunchX, LaunchY, LaunchZ), NAME_None, true);
		}

		Destroy();
	}
}