#pragma once

#include "CoreMinimal.h"
#include "Gameplay/HUDs/SoarHUD.h"
#include "SoarLobbyHUD.generated.h"

UCLASS()
class SOAR_API ASoarLobbyHUD : public ASoarHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

private:
	void HandleLoginComplete(bool bInWasSuccessful, const FString& InError);

	FDelegateHandle LoginCompleteHandle;
};
