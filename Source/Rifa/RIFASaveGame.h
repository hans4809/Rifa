#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RIFASaveGame.generated.h"

UCLASS()
class RIFA_API URIFASaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URIFASaveGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FVector SavePosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		TArray<int> ItemList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SoundTrack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FString SaveSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 SaveIndex;
};