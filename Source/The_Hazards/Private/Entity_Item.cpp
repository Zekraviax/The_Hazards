#include "Entity_Item.h"


// Functions
// --------------------------------------------------

// ------------------------- Base actor functions
// Sets default values
AEntity_Item::AEntity_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CubeMesh->SetSimulatePhysics(true);
	//CubeMesh->SetEnableGravity(true);

	// Construct actor components
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	OuterBoxCollider = CreateDefaultSubobject<UBoxComponent>("OuterBoxCollider");
	InnerBoxCollider = CreateDefaultSubobject<UBoxComponent>("InnerBoxCollider");

	// Attach components
	CubeMesh->SetupAttachment(RootComponent);
	OuterBoxCollider->SetupAttachment(CubeMesh);
	InnerBoxCollider->SetupAttachment(CubeMesh);
}


void AEntity_Item::BeginPlay()
{
	CubeMesh->SetSimulatePhysics(true);
	CubeMesh->SetEnableGravity(true);
}


void AEntity_Item::OnPlayerBeginOverlap(AEntity_Player* PlayerReference)
{
	if (PlayerReference) {
		PlayerReference->InteractableEntities.AddUnique(this);
	}
}


void AEntity_Item::OnPlayerEndOverlap(AEntity_Player* PlayerReference)
{
	if (PlayerReference) {
		PlayerReference->InteractableEntities.Remove(this);
	}
}


void AEntity_Item::OnPlayerInteract(AEntity_Player* PlayerReference)
{
	if (PlayerReference) {
		for (int i = 0; i < Items.Num(); i++) {
			PlayerReference->AddItemToInventory(Items[i]);
		}

		if (Money > 0) {
			PlayerReference->Money += Money;
		}

		if (Scrap > 0) {
			PlayerReference->Scrap += Scrap;
		}

		Destroy(this);
	}
}