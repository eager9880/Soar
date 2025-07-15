#include "Gameplay/HUDs/SoarLobbyHUD.h"

#include "Network/SoarClientNetworkSubsystem.h"
#include "UI/Widgets/Lobby/SoarLobbyScreen.h"

void ASoarLobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	LoginCompleteHandle = CLIENTNETWORK->OnLoginComplete.AddUObject(this, &ASoarLobbyHUD::HandleLoginComplete);
}

void ASoarLobbyHUD::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	CLIENTNETWORK->OnLoginComplete.Remove(LoginCompleteHandle);

	Super::EndPlay(InEndPlayReason);
}

void ASoarLobbyHUD::HandleLoginComplete(bool bInWasSuccessful, const FString& InError)
{
	if (bInWasSuccessful)
	{
		ShowScreen<USoarLobbyScreen>();
	}
	else
	{
		// Dialog
	}
}
