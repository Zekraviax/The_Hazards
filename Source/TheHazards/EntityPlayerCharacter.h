#pragma once


#include "CoreMinimal.h"
#include "EntityBaseCharacter.h"
#include "EntityPlayerCharacter.generated.h"


UCLASS()
class THEHAZARDS_API AEntityPlayerCharacter : public AEntityBaseCharacter
{
	GENERATED_BODY()


public:
	// Pause the game and open the pause menu, or
	// Close one menu and open another related menu
	void PauseGame();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
};
