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
	TMap <EItem, bool> SoundItemHavingMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap <EItem, bool> SoundItemOnOffMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SoundTrack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<EHairPartsItem> CurrentHairPartsArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<ECharacterMaterialItem> CurrentMaterialItemArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> FlyItemArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> SwimItemArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> LevelSequencePlayerArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	ECharacterMaterialItem ECurrentCharacterMaterial;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	EHairPartsItem ECurrentCharacterHairPart;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap<ETutorialType, bool> IsTutorialFinishedMap;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	bool bCanFly;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	bool bCanSwim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName CurrentLevelName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	bool bClearIslandForest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	bool bClearFieldForest;
};
