#include "Gameplay/HUDs/SoarHUD.h"

#include "UI/Widgets/SoarScreen.h"

TWeakObjectPtr<ASoarHUD> ASoarHUD::Get(TObjectPtr<UWorld> InWorld)
{
	TObjectPtr<APlayerController> PlayerController = InWorld ? InWorld->GetFirstPlayerController() : nullptr;

	return PlayerController ? PlayerController->GetHUD<ASoarHUD>() : nullptr;
}

void ASoarHUD::ShowScreen(TSubclassOf<USoarScreen> InScreenClass)
{
	if (!InScreenClass)
	{
		return;
	}

	if (InScreenClass->IsInBlueprint())
	{
		InScreenClass = InScreenClass->GetSuperClass();
	}

	TSubclassOf<USoarScreen> ScreenClass = ScreenClasses.FindRef(InScreenClass);

	if (!ScreenClass || !ScreenStack.IsEmpty() && ScreenStack.Last() == InScreenClass)
	{
		return;
	}

	ScreenStack.Push(InScreenClass);

	TObjectPtr<USoarScreen>& Screen = Screens.FindOrAdd(InScreenClass);

	if (!Screen)
	{
		Screen = CreateWidget<USoarScreen>(GetWorld(), ScreenClass);
	}

	Screen->Show(ScreenStack.Num(), true);
}

void ASoarHUD::HideScreen(TSubclassOf<USoarScreen> InScreenClass)
{
	if (!InScreenClass)
	{
		return;
	}

	if (InScreenClass->IsInBlueprint())
	{
		InScreenClass = InScreenClass->GetSuperClass();
	}

	TObjectPtr<USoarScreen> Screen = Screens.FindRef(InScreenClass);

	if (!Screen || ScreenStack.IsEmpty() || ScreenStack.Last() != InScreenClass)
	{
		return;
	}

	ScreenStack.Pop();

	if (TObjectPtr<USoarScreen> PrevScreen = !ScreenStack.IsEmpty() ? Screens.FindRef(ScreenStack.Last()) : nullptr)
	{
		PrevScreen->Show(ScreenStack.Num(), false);
	}

	Screen->Hide(true);
}

void ASoarHUD::HidePrevScreen()
{
	if (TObjectPtr<USoarScreen> PrevScreen = ScreenStack.Num() > 1 ? Screens.FindRef(ScreenStack.Last(1)) : nullptr)
	{
		PrevScreen->Hide(false);
	}
}

void ASoarHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowScreen(DefaultScreenClass);
}
