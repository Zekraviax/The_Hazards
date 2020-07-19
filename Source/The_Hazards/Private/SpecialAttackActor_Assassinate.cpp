#include "SpecialAttackActor_Assassinate.h"

#include "Entity_Base.h"


void ASpecialAttackActor_Assassinate::OnEntityOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AttackingEntity && SpecialAttackLibrary_Reference) {
		if (OtherActor && OtherComp && (OtherActor != this) && (OtherActor != AttackingEntity) && (Cast<AEntity_Base>(OtherActor)) && (OtherActor != SpecialAttackLibrary_Reference->LinkedEntity) && (OtherComp->GetName().Contains("BoxCollider")) && (OtherComp->GetOwner() != AttackingEntity) && !AttackedEntitiesArray.Contains(Cast<AEntity_Base>(OtherActor)))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Overlap Begin  /  Actor: " + this->GetName() + "  /  Other Actor: " + OtherActor->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Overlapped Component: " + OverlappedComp->GetName() + "  /  Other Component: " + OtherComp->GetName()));
			AttackedEntitiesArray.Add(Cast<AEntity_Base>(OtherActor));

			// Find two actor's look directions
			FRotator AttackingEntityLookAtVector = AttackingEntity->RotatingCore->GetComponentRotation();
			AttackingEntityLookAtVector.Normalize();
			FRotator OtherEntityLookAtVector = OtherActor->GetActorRotation();
			OtherEntityLookAtVector.Normalize();

			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, FString::Printf(TEXT("Attacking Entity Forward Vector: %s"), *AttackingEntityLookAtVector.ToString()));
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, FString::Printf(TEXT("Other Entity Forward Vector: %s"), *OtherEntityLookAtVector.ToString()));

			// Check if attacking entity is behind enough other entity
			if (AttackingEntityLookAtVector.Yaw >= (OtherEntityLookAtVector.Yaw - 45) && AttackingEntityLookAtVector.Yaw <= (OtherEntityLookAtVector.Yaw + 45)) {
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Backstab!"));
				Cast<AEntity_Base>(OtherActor)->EntityHit(50);
			} else {
				Cast<AEntity_Base>(OtherActor)->EntityHit(25);
			}
		}
	}
}