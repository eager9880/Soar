#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoarPlayerCharacter.generated.h"

UCLASS()
class SOAR_API ASoarPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASoarPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> CameraBoomComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp;
};
