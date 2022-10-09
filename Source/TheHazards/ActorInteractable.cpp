#include "ActorInteractable.h"


#include "EntityBaseCharacter.h"


// Sets default values
AActorInteractable::AActorInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup interact bounds
	InteractBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBounds"));
	InteractBounds->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AActorInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AActorInteractable::OnInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Interacted With Actor: %s"), *GetFullName()));

	return true;
}

