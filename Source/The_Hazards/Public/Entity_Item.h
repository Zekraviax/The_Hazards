#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TheHazards_GameMode.h"

#include "Entity_Item.generated.h"

// Forward Declarations
class AEntity_Player;


UCLASS()
class THE_HAZARDS_API AEntity_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntity_Item();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* OuterBoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* InnerBoxCollider;

// ------------------------- Items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<F_Item_BaseStruct> Items;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnPlayerBeginOverlap(AEntity_Player* PlayerReference);

	UFUNCTION(BlueprintCallable)
	void OnPlayerEndOverlap(AEntity_Player* PlayerReference);

	UFUNCTION()
	void OnPlayerInteract(AEntity_Player* PlayerReference);
};
