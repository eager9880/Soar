#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoarClientNetworkSubsystem.generated.h"

#define CLIENTNETWORK	USoarClientNetworkSubsystem::Get(GetWorld())

UCLASS()
class SOAR_API USoarClientNetworkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static TWeakObjectPtr<USoarClientNetworkSubsystem> Get(TObjectPtr<UWorld> InWorld);

	void Login();

	DECLARE_EVENT_TwoParams(USoarClientNetworkSubsystem, FSoarOnLoginComplete, bool, const FString&)
	FSoarOnLoginComplete OnLoginComplete;

private:
	void HandleLoginComplete(int32 InLocalUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InError);

	FDelegateHandle LoginCompleteHandle;
};
