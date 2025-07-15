#include "DataAssets/GameData/SoarGameDataAsset.h"

#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

#include "Core/SoarGameInstance.h"

TWeakObjectPtr<USoarGameDataAsset> USoarGameDataAsset::Get(TObjectPtr<UWorld> InWorld)
{
	TObjectPtr<USoarGameInstance> GameInstance = InWorld ? InWorld->GetGameInstance<USoarGameInstance>() : nullptr;

	return GameInstance ? GameInstance->GetDataAsset<USoarGameDataAsset>() : nullptr;
}

FText USoarGameDataAsset::GetLocText(const FTextKey& InKey, const FStringFormatOrderedArguments& InOrderedArguments) const
{
	FString SourceString;

	if (TObjectPtr<UStringTable> StringTable = StringTables.FindRef(TEXT("ko-KR")))
	{
		StringTable->GetStringTable()->GetSourceString(InKey, SourceString);
	}

	return FText::FromString(FString::Format(*SourceString, InOrderedArguments));
}
