#pragma once


#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "TheHazardsVariables.h"

#include "ActorComponentInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEHAZARDS_API UActorComponentInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorComponentInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedHeadItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedPrimaryWeapon;

	// List of uneqipped items in this character's inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemBase> ItemsList;

	// ?
	UFUNCTION()
	void ReturnEquippedWeaponsData(float& DamagePerShot);
};
