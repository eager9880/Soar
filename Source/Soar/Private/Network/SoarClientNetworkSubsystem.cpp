#include "Network/SoarClientNetworkSubsystem.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

TWeakObjectPtr<USoarClientNetworkSubsystem> USoarClientNetworkSubsystem::Get(TObjectPtr<UWorld> InWorld)
{
	TObjectPtr<UGameInstance> GameInstance = InWorld ? InWorld->GetGameInstance() : nullptr;

	return GameInstance ? GameInstance->GetSubsystem<USoarClientNetworkSubsystem>() : nullptr;
}

void USoarClientNetworkSubsystem::Login()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	IOnlineIdentityPtr OnlineIdentity = OnlineSubsystem ? OnlineSubsystem->GetIdentityInterface() : nullptr;

	if (!OnlineIdentity || OnlineIdentity->GetUniquePlayerId(0) && OnlineIdentity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		return;
	}

	if (!LoginCompleteHandle.IsValid())
	{
		LoginCompleteHandle = OnlineIdentity->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &USoarClientNetworkSubsystem::HandleLoginComplete));
	}

	FOnlineAccountCredentials AccountCredentials;
	AccountCredentials.Type = TEXT("AccountPortal");

	if (!OnlineIdentity->Login(0, AccountCredentials))
	{
		OnlineIdentity->ClearOnLoginCompleteDelegate_Handle(0, LoginCompleteHandle);
		LoginCompleteHandle.Reset();
	}
}

void USoarClientNetworkSubsystem::HandleLoginComplete(int32 InLocalUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InError)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (IOnlineIdentityPtr OnlineIdentity = OnlineSubsystem ? OnlineSubsystem->GetIdentityInterface() : nullptr)
	{
		OnlineIdentity->ClearOnLoginCompleteDelegate_Handle(InLocalUserNum, LoginCompleteHandle);
	}

	LoginCompleteHandle.Reset();

	OnLoginComplete.Broadcast(bInWasSuccessful, InError);
}
