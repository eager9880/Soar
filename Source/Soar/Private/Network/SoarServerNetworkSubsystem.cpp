#include "Network/SoarServerNetworkSubsystem.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

TWeakObjectPtr<USoarServerNetworkSubsystem> USoarServerNetworkSubsystem::Get(TObjectPtr<UWorld> InWorld)
{
	TObjectPtr<UGameInstance> GameInstance = InWorld ? InWorld->GetGameInstance() : nullptr;

	return GameInstance ? GameInstance->GetSubsystem<USoarServerNetworkSubsystem>() : nullptr;
}

void USoarServerNetworkSubsystem::CreateSession()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr;

	if (!OnlineSession)
	{
		return;
	}

	if (!CreateSessionCompleteHandle.IsValid())
	{
		CreateSessionCompleteHandle = OnlineSession->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &USoarServerNetworkSubsystem::HandleCreateSessionComplete));
	}

	FOnlineSessionSettings SessionSettings;
	SessionSettings.NumPublicConnections = 16;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = true;
	SessionSettings.bUsesStats = true;
	SessionSettings.Set(TEXT("MODE"), FString(TEXT("SOLO")), EOnlineDataAdvertisementType::ViaOnlineService);

	if (!OnlineSession->CreateSession(0, NAME_GameSession, SessionSettings))
	{
		OnlineSession->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteHandle);
		CreateSessionCompleteHandle.Reset();
	}
}

void USoarServerNetworkSubsystem::StartSession()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr;

	if (!OnlineSession)
	{
		return;
	}

	if (!StartSessionCompleteHandle.IsValid())
	{
		StartSessionCompleteHandle = OnlineSession->AddOnStartSessionCompleteDelegate_Handle(FOnStartSessionCompleteDelegate::CreateUObject(this, &USoarServerNetworkSubsystem::HandleStartSessionComplete));
	}

	if (!OnlineSession->StartSession(NAME_GameSession))
	{
		OnlineSession->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteHandle);
		StartSessionCompleteHandle.Reset();
	}
}

void USoarServerNetworkSubsystem::RegisterPlayer(const FUniqueNetId& InPlayerId)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr;

	if (!OnlineSession)
	{
		return;
	}

	if (!RegisterPlayersCompleteHandle.IsValid())
	{
		RegisterPlayersCompleteHandle = OnlineSession->AddOnRegisterPlayersCompleteDelegate_Handle(FOnRegisterPlayersCompleteDelegate::CreateUObject(this, &USoarServerNetworkSubsystem::HandleRegisterPlayersComplete));
	}

	if (!OnlineSession->RegisterPlayer(NAME_GameSession, InPlayerId, false))
	{
		OnlineSession->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayersCompleteHandle);
		RegisterPlayersCompleteHandle.Reset();
	}
}

void USoarServerNetworkSubsystem::UnregisterPlayer(const FUniqueNetId& InPlayerId)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr;

	if (!OnlineSession)
	{
		return;
	}

	if (!UnregisterPlayersCompleteHandle.IsValid())
	{
		UnregisterPlayersCompleteHandle = OnlineSession->AddOnUnregisterPlayersCompleteDelegate_Handle(FOnUnregisterPlayersCompleteDelegate::CreateUObject(this, &USoarServerNetworkSubsystem::HandleUnregisterPlayersComplete));
	}

	if (!OnlineSession->UnregisterPlayer(NAME_GameSession, InPlayerId))
	{
		OnlineSession->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayersCompleteHandle);
		UnregisterPlayersCompleteHandle.Reset();
	}
}

void USoarServerNetworkSubsystem::EndSession()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr;

	if (!OnlineSession)
	{
		return;
	}

	if (!EndSessionCompleteHandle.IsValid())
	{
		EndSessionCompleteHandle = OnlineSession->AddOnEndSessionCompleteDelegate_Handle(FOnEndSessionCompleteDelegate::CreateUObject(this, &USoarServerNetworkSubsystem::HandleEndSessionComplete));
	}

	if (!OnlineSession->EndSession(NAME_GameSession))
	{
		OnlineSession->ClearOnEndSessionCompleteDelegate_Handle(EndSessionCompleteHandle);
		EndSessionCompleteHandle.Reset();
	}
}

void USoarServerNetworkSubsystem::DestroySession()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr;

	if (!OnlineSession)
	{
		return;
	}

	if (!DestroySessionCompleteHandle.IsValid())
	{
		DestroySessionCompleteHandle = OnlineSession->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(this, &USoarServerNetworkSubsystem::HandleDestroySessionComplete));
	}

	if (!OnlineSession->DestroySession(NAME_GameSession))
	{
		OnlineSession->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteHandle);
		DestroySessionCompleteHandle.Reset();
	}
}

void USoarServerNetworkSubsystem::HandleCreateSessionComplete(FName InSessionName, bool bInWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr)
	{
		OnlineSession->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteHandle);
	}

	CreateSessionCompleteHandle.Reset();
}

void USoarServerNetworkSubsystem::HandleStartSessionComplete(FName InSessionName, bool bInWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr)
	{
		OnlineSession->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteHandle);
	}

	StartSessionCompleteHandle.Reset();
}

void USoarServerNetworkSubsystem::HandleRegisterPlayersComplete(FName InSessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bInWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr)
	{
		OnlineSession->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayersCompleteHandle);
	}

	RegisterPlayersCompleteHandle.Reset();
}

void USoarServerNetworkSubsystem::HandleUnregisterPlayersComplete(FName InSessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bInWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr)
	{
		OnlineSession->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayersCompleteHandle);
	}

	UnregisterPlayersCompleteHandle.Reset();
}

void USoarServerNetworkSubsystem::HandleEndSessionComplete(FName InSessionName, bool bInWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr)
	{
		OnlineSession->ClearOnEndSessionCompleteDelegate_Handle(EndSessionCompleteHandle);
	}

	EndSessionCompleteHandle.Reset();
}

void USoarServerNetworkSubsystem::HandleDestroySessionComplete(FName InSessionName, bool bInWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineSessionPtr OnlineSession = OnlineSubsystem ? OnlineSubsystem->GetSessionInterface() : nullptr)
	{
		OnlineSession->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteHandle);
	}

	DestroySessionCompleteHandle.Reset();
}
