#include "UI/Widgets/SoarScreen.h"

#include "Animation/WidgetAnimation.h"

#include "Gameplay/HUDs/SoarHUD.h"

void USoarScreen::Show(int32 InZOrder, bool bInPlayAnim)
{
	SetVisibility(ESlateVisibility::Collapsed);

	AddToViewport(InZOrder);

	if (ShowAnim && bInPlayAnim)
	{
		PlayAnimation(ShowAnim);
	}
	else
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		if (bInPlayAnim)
		{
			HandleShowAnimFinished();
		}
	}
}

void USoarScreen::Hide(bool bInPlayAnim)
{
	if (HideAnim && bInPlayAnim)
	{
		PlayAnimation(HideAnim);
	}
	else
	{
		RemoveFromParent();
	}
}

void USoarScreen::NativeConstruct()
{
	Super::NativeConstruct();

	if (ShowAnim)
	{
		FWidgetAnimationDynamicEvent OnShowAnimFinished;
		OnShowAnimFinished.BindDynamic(this, &USoarScreen::HandleShowAnimFinished);
		BindToAnimationFinished(ShowAnim, OnShowAnimFinished);
	}

	if (HideAnim)
	{
		FWidgetAnimationDynamicEvent OnHideAnimFinished;
		OnHideAnimFinished.BindDynamic(this, &USoarScreen::RemoveFromParent);
		BindToAnimationFinished(HideAnim, OnHideAnimFinished);
	}
}

void USoarScreen::HandleShowAnimFinished()
{
	HUD->HidePrevScreen();
}
