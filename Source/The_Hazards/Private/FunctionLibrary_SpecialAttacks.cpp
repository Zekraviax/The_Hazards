#include "FunctionLibrary_SpecialAttacks.h"


// Define Special Attack Indices
#define ASSASSINATE 1
#define DOWNWARDS_STRIKE 2
#define PARRY 3
#define SWING_AROUND 4

// Initialize Special Attacks
void AFunctionLibrary_SpecialAttacks::InitializeSpecialAttacks()
{
	SpecialAttackFunctions[ASSASSINATE] = &AFunctionLibrary_SpecialAttacks::Assassinate;
	SpecialAttackFunctions[DOWNWARDS_STRIKE] = &AFunctionLibrary_SpecialAttacks::Downwards_Strike;
	SpecialAttackFunctions[PARRY] = &AFunctionLibrary_SpecialAttacks::Parry;
	SpecialAttackFunctions[SWING_AROUND] = &AFunctionLibrary_SpecialAttacks::Swing_Around;
}

//void AFunctionLibrary_SpecialAttacks::SpawnSpecialAttackActor(E_Weapon_SpecialAttacks SpecialAttack)
//{
//
//}

// ------------------------- Dagger
void AFunctionLibrary_SpecialAttacks::Assassinate()
{
	FActorSpawnParameters SpawnInfo;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Special Attack: Assassinate"));

	SpecialAttackActor_Reference = GetWorld()->SpawnActor<ASpecialAttackActor_Base>(Assassinate_Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
}

// ------------------------- Broadsword
void AFunctionLibrary_SpecialAttacks::Downwards_Strike()
{

}

// ------------------------- Rapier
void AFunctionLibrary_SpecialAttacks::Parry()
{

}

// ------------------------- Flail
void AFunctionLibrary_SpecialAttacks::Swing_Around()
{

}

// Call Special Attacks
void AFunctionLibrary_SpecialAttacks::CallSpecialAttackFunction(E_Weapon_SpecialAttacks SpecialAttack)
{
	//uint8 SpecialAttackEnumToByte = (uint8)SpecialAttack;

	//(this->* (SpecialAttackFunctions[SpecialAttackEnumToByte]))();

	FActorSpawnParameters SpawnInfo;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);

	switch (SpecialAttack) {
		case(E_Weapon_SpecialAttacks::E_Assassinate):
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Special Attack: Assassinate"));

			if (Assassinate_Class)
				SpecialAttackActor_Reference = GetWorld()->SpawnActor<ASpecialAttackActor_Base>(Assassinate_Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Special Attack Error"));
			break;
	}

	if (SpecialAttackActor_Reference) {
		//SpecialAttackActor_Reference->AttachToActor(Cast<AActor>(LinkedEntity), FAttachmentTransformRules::SnapToTargetIncludingScale);
		SpecialAttackActor_Reference->AttachToComponent(LinkedEntity->WeaponCollider, AttachmentRules);
	}
}