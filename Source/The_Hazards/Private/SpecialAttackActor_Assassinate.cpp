#include "SpecialAttackActor_Assassinate.h"

#include "Entity_Base.h"


void ASpecialAttackActor_Assassinate::OnEntityOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && (OtherActor != this) && (OtherActor != AttackingEntity) && (OtherActor != SpecialAttackLibrary_Reference->LinkedEntity) && (Cast<AEntity_Base>(OtherActor)) && (OtherComp->GetName().Contains("BoxCollider")) && (OtherComp->GetOwner() != AttackingEntity) && !AttackedEntitiesArray.Contains(Cast<AEntity_Base>(OtherActor)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Overlap Begin  /  Actor: " + this->GetName() + "  /  Other Actor: " + OtherActor->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Overlapped Component: " + OverlappedComp->GetName() + "  /  Other Component: " + OtherComp->GetName()));

		AttackedEntitiesArray.Add(Cast<AEntity_Base>(OtherActor));
		//Cast<AEntity_Base>(OtherActor)->EntityHit(20);
	}
}