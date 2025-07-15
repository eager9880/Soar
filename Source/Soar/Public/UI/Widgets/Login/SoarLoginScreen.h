#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/SoarScreen.h"
#include "SoarLoginScreen.generated.h"

UCLASS()
class SOAR_API USoarLoginScreen : public USoarScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> LoginButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LoginText;

private:
	UFUNCTION()
	void HandleLoginButtonClicked();

	void HandleLoginComplete(bool bInWasSuccessful, const FString& InError);

	FDelegateHandle LoginCompleteHandle;
};
