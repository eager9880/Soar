#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoarGameDataAsset.generated.h"

#define GAMEDATA	USoarGameDataAsset::Get(GetWorld())
#define SLOCTEXT	GAMEDATA->GetLocText

UCLASS()
class SOAR_API USoarGameDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	static TWeakObjectPtr<USoarGameDataAsset> Get(TObjectPtr<UWorld> InWorld);

	template <typename T>
	FORCEINLINE const T* FindData(FName InKey) const
	{
		TObjectPtr<UDataTable> DataTable = DataTables.FindRef(T::StaticStruct());

		return DataTable ? DataTable->FindRow<T>(InKey, TEXT("")) : nullptr;
	}

	FText GetLocText(const FTextKey& InKey, const FStringFormatOrderedArguments& InOrderedArguments = {}) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<TObjectPtr<UScriptStruct>, TObjectPtr<UDataTable>> DataTables;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TObjectPtr<UStringTable>> StringTables;
};
