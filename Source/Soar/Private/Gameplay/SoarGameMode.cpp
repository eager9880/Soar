#include "Gameplay/SoarGameMode.h"

#include "GameFramework/PlayerState.h"

#include "Network/SoarServerNetworkSubsystem.h"

void ASoarGameMode::InitGame(const FString& InMapName, const FString& InOptions, FString& OutErrorMessage)
{
	Super::InitGame(InMapName, InOptions, OutErrorMessage);

	SERVERNETWORK->CreateSession();
}

void ASoarGameMode::Logout(AController* InExiting)
{
	TObjectPtr<APlayerState> PlayerState = InExiting ? InExiting->PlayerState : nullptr;
	const FUniqueNetIdRepl& PlayerId = PlayerState ? PlayerState->GetUniqueId() : nullptr;

	if (PlayerId.IsValid())
	{
		SERVERNETWORK->UnregisterPlayer(*PlayerId);
	}

	Super::Logout(InExiting);
}

void ASoarGameMode::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	SERVERNETWORK->DestroySession();

	Super::EndPlay(InEndPlayReason);
}

FString ASoarGameMode::InitNewPlayer(APlayerController* InNewPlayerController, const FUniqueNetIdRepl& InUniqueId, const FString& InOptions, const FString& InPortal)
{
	FString ErrorMessage = Super::InitNewPlayer(InNewPlayerController, InUniqueId, InOptions, InPortal);

	if (InUniqueId.IsValid())
	{
		SERVERNETWORK->RegisterPlayer(*InUniqueId);
	}

	return ErrorMessage;
}

void ASoarGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	SERVERNETWORK->StartSession();
}

void ASoarGameMode::HandleMatchHasEnded()
{
	SERVERNETWORK->EndSession();

	Super::HandleMatchHasEnded();
}
