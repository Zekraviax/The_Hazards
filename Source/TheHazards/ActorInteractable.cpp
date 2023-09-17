#include "ActorInteractable.h"


#include "EntityBaseCharacter.h"


// Sets default values
AActorInteractable::AActorInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(GetRootComponent());

	// Setup interact bounds
	InteractBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBounds"));
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

