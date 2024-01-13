#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyGameInstance.h"
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
	TMap <Item, bool> SoundItemMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SoundTrack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap<EHairPartsItem, TObjectPtr<USkeletalMesh>> HairPartsMap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap<ECharacterMaterialItem, TObjectPtr<UMaterialInterface>> CharacterMaterialMap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> FlyItemArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> SwimItemArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> LevelSequencePlayerArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TObjectPtr<UMaterialInterface> CurrentCharacterMaterial;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TObjectPtr<USkeletalMesh> CurrentHairPart;
};
