#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SoarHUD.generated.h"

#define HUD	ASoarHUD::Get(GetWorld())

UCLASS()
class SOAR_API ASoarHUD : public AHUD
{
	GENERATED_BODY()

public:
	static TWeakObjectPtr<ASoarHUD> Get(TObjectPtr<UWorld> InWorld);

	void ShowScreen(TSubclassOf<class USoarScreen> InScreenClass);

	template <typename T>
	FORCEINLINE void ShowScreen()
	{
		ShowScreen(T::StaticClass());
	}

	void HideScreen(TSubclassOf<class USoarScreen> InScreenClass);

	template <typename T>
	FORCEINLINE void HideScreen()
	{
		HideScreen(T::StaticClass());
	}

	void HidePrevScreen();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<class USoarScreen>, TSubclassOf<class USoarScreen>> ScreenClasses;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USoarScreen> DefaultScreenClass;

private:
	UPROPERTY(Transient)
	TMap<TSubclassOf<class USoarScreen>, TObjectPtr<class USoarScreen>> Screens;

	UPROPERTY(Transient)
	TArray<TSubclassOf<class USoarScreen>> ScreenStack;
};
