#include "Gameplay/Characters/SoarPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASoarPlayerCharacter::ASoarPlayerCharacter()
	: CameraBoomComp(CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomComp")))
	, CameraComp(CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp")))
{
	bUseControllerRotationYaw = false;

	if (TObjectPtr<UCharacterMovementComponent> MovementComp = GetCharacterMovement())
	{
		MovementComp->bOrientRotationToMovement = true;
	}

	if (CameraBoomComp)
	{
		CameraBoomComp->SetupAttachment(RootComponent);
		CameraBoomComp->bUsePawnControlRotation = true;
	}

	if (CameraComp)
	{
		CameraComp->SetupAttachment(CameraBoomComp);
	}
}
