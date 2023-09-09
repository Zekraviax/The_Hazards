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
			float RandomSpawnX = FMath::RandRange(-20.f, 20.f);
			float RandomSpawnY = FMath::RandRange(-20.f, 20.f);
			FVector SpawnLocation = FVector((GetActorLocation().X + RandomSpawnX), (GetActorLocation().Y + RandomSpawnY), GetActorLocation().Z + 2.5f);

			AActorInteractableItem* ItemObject = GetWorld()->SpawnActor<AActorInteractableItem>(InteractableItemBlueprintClass, SpawnLocation, GetActorRotation(), SpawnInfo);
			ItemObject->GetInventoryComponent()->ItemsList.Add(Item);

			FVector Location = ItemObject->GetActorLocation();
			float LaunchX = (FMath::RandRange(-10.f, 10.f)) * 5;
			float LaunchY = (FMath::RandRange(-10.f, 10.f)) * 5;
			float LaunchZ = 500.f;

			ItemObject->GetMeshComponent()->AddImpulse(FVector(LaunchX, LaunchY, LaunchZ), NAME_None, true);
		}

		Destroy();
	}
}