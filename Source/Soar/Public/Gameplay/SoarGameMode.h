#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SoarGameMode.generated.h"

UCLASS()
class SOAR_API ASoarGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& InMapName, const FString& InOptions, FString& OutErrorMessage) override;

	virtual void Logout(AController* InExiting) override;

protected:
	virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

	virtual FString InitNewPlayer(APlayerController* InNewPlayerController, const FUniqueNetIdRepl& InUniqueId, const FString& InOptions, const FString& InPortal = TEXT("")) override;

	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
};
