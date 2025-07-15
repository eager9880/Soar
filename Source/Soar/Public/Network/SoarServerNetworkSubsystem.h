#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoarServerNetworkSubsystem.generated.h"

#define SERVERNETWORK	USoarServerNetworkSubsystem::Get(GetWorld())

UCLASS()
class SOAR_API USoarServerNetworkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static TWeakObjectPtr<USoarServerNetworkSubsystem> Get(TObjectPtr<UWorld> InWorld);

	void CreateSession();
	void StartSession();
	void RegisterPlayer(const FUniqueNetId& InPlayerId);
	void UnregisterPlayer(const FUniqueNetId& InPlayerId);
	void EndSession();
	void DestroySession();

private:
	void HandleCreateSessionComplete(FName InSessionName, bool bInWasSuccessful);
	void HandleStartSessionComplete(FName InSessionName, bool bInWasSuccessful);
	void HandleRegisterPlayersComplete(FName InSessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bInWasSuccessful);
	void HandleUnregisterPlayersComplete(FName InSessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bInWasSuccessful);
	void HandleEndSessionComplete(FName InSessionName, bool bInWasSuccessful);
	void HandleDestroySessionComplete(FName InSessionName, bool bInWasSuccessful);

	FDelegateHandle CreateSessionCompleteHandle;
	FDelegateHandle StartSessionCompleteHandle;
	FDelegateHandle RegisterPlayersCompleteHandle;
	FDelegateHandle UnregisterPlayersCompleteHandle;
	FDelegateHandle EndSessionCompleteHandle;
	FDelegateHandle DestroySessionCompleteHandle;
};
