#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SoarGameInstance.generated.h"

UCLASS()
class SOAR_API USoarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	template <typename T>
	FORCEINLINE TWeakObjectPtr<T> GetDataAsset() const
	{
		return Cast<T>(DataAssets.FindRef(T::StaticClass()));
	}

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UDataAsset>, TObjectPtr<UDataAsset>> DataAssets;
};
