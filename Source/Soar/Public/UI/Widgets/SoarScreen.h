#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoarScreen.generated.h"

UCLASS()
class SOAR_API USoarScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show(int32 InZOrder, bool bInPlayAnim);
	void Hide(bool bInPlayAnim);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> ShowAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> HideAnim;

private:
	UFUNCTION()
	void HandleShowAnimFinished();
};
