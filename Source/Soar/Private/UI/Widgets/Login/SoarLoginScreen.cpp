#include "UI/Widgets/Login/SoarLoginScreen.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "DataAssets/GameData/SoarGameDataAsset.h"
#include "Network/SoarClientNetworkSubsystem.h"

void USoarLoginScreen::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &USoarLoginScreen::HandleLoginButtonClicked);
	}

	if (LoginText)
	{
		LoginText->SetText(SLOCTEXT(TEXT("Login")));
	}

	LoginCompleteHandle = CLIENTNETWORK->OnLoginComplete.AddUObject(this, &USoarLoginScreen::HandleLoginComplete);
}

void USoarLoginScreen::NativeDestruct()
{
	CLIENTNETWORK->OnLoginComplete.Remove(LoginCompleteHandle);

	Super::NativeDestruct();
}

void USoarLoginScreen::HandleLoginButtonClicked()
{
	if (LoginButton)
	{
		LoginButton->SetIsEnabled(false);
	}

	CLIENTNETWORK->Login();
}

void USoarLoginScreen::HandleLoginComplete(bool bInWasSuccessful, const FString& InError)
{
	if (LoginButton)
	{
		LoginButton->SetIsEnabled(!bInWasSuccessful);
	}
}
