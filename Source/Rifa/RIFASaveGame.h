#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyGameInstance.h"
#include "RIFASaveGame.generated.h"

UENUM()
enum class EHairPartsItem : uint8 
{
	First,
	Second,
	Third,
	MaxCount
};

UENUM()
enum class ECharacterMaterialItem : uint8
{
	Default UMETA(DisplayName = "Default"),
	White UMETA(DisplayName = "White"),
	Blue UMETA(DisplayName = "Blue"),
	Green UMETA(DisplayName = "Green"),
	Red UMETA(DisplayName = "Red"),
	Yellow UMETA(DisplayName = "Yellow"),
	MaxCount
}; 

UCLASS()
class RIFA_API URIFASaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URIFASaveGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FVector SavePosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap <Item, bool> ItemMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SoundTrack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap<EHairPartsItem, USkeletalMesh*> HairPartsMap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap<ECharacterMaterialItem, UMaterialInterface*> CharacterMaterialMap;
};