#include "Entity_Item.h"

#include "Entity_Player.h"


// Functions
// --------------------------------------------------

// ------------------------- Base actor functions
// Sets default values
AEntity_Item::AEntity_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct actor components
	//BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	OuterBoxCollider = CreateDefaultSubobject<UBoxComponent>("OuterBoxCollider");
	InnerBoxCollider = CreateDefaultSubobject<UBoxComponent>("InnerBoxCollider");

	// Attach components
	//BoxComponent->SetupAttachment(RootComponent);
	CubeMesh->SetupAttachment(RootComponent);
	OuterBoxCollider->SetupAttachment(CubeMesh);
	InnerBoxCollider->SetupAttachment(CubeMesh);
}


void AEntity_Item::BeginPlay()
{
	//CubeMesh->SetSimulatePhysics(true);
	//CubeMesh->SetEnableGravity(true);
}


// Called every frame
void AEntity_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			Items[i].Amount--;
		}

		if (Money > 0) {
			PlayerReference->Money += Money;
		}

		if (Scrap > 0) {
			PlayerReference->Scrap += Scrap;
		}

		this->Destroy(true, true);
	}
}