// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"
/**
 * 
 */

UENUM()
enum class Item : uint8
{
	Piano_1_Medium,
	WindInstrument_1_Medium,
	Bell_1_High,
	Voice_1_Women,
	Piano_1_High,
	StringInstrument_1_Medium,
	Piano_2_Low,
	WindInstrument_2_Medium,
	Voice_2_Men,
	PercussionInstrument_1_Low,
	StringInstrument_2_Medium,
	Piano_2_High,
	StringInstrument_3_High,
	Bell_2_High,
	PercussionInstrument_3_High,
	StringInstrument_4_High,
	MaxCount
};

UENUM()
enum class EHairPartsItem : uint8
{
	Default UMETA(DisplayName = "Default"),
	First UMETA(DisplayName = "First"),
	Second UMETA(DisplayName = "Second"),
	Third UMETA(DisplayName = "Third"),
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
	Black UMETA(DisplayName = "Black"),
	MaxCount
};

UENUM()
enum class ETutorialType : uint8
{
	Movement UMETA(DisplayName = "Movement"),
	Jump UMETA(DisplayName = "Jump"),
	Dash UMETA(DisplayName = "Dash"),
	Fly UMETA(DisplayName = "Fly"),
	Swim UMETA(DisplayName = "Swim"),
	Pickup UMETA(DisplayName = "Pickup"),
	MaxCount
};

UCLASS()
class RIFA_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	FVector SavePosition;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TMap <Item, bool> SoundItemHavingMap;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TMap <Item, bool> SoundItemOnOffMap;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	FString SoundTrack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<EHairPartsItem> CurrentHairPartsArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<ECharacterMaterialItem> CurrentMaterialItemArr;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TMap<EHairPartsItem, TObjectPtr<USkeletalMesh>> HairPartsMeshMap;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TMap<ECharacterMaterialItem, TObjectPtr<UMaterialInterface>> HairMaterialMap;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TMap<ECharacterMaterialItem, TObjectPtr<UMaterialInterface>> CharacterMaterialMap;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> FlyItemArr;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> SwimItemArr;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveData")
	TArray<bool> LevelSequencePlayerArr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ECharacterMaterialItem ECurrentCharacterMaterial;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	EHairPartsItem ECurrentCharacterHairPart;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TMap<ETutorialType, class UTexture2D*> TutorialImageMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PopupSort = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BGMVolume = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SFXVolume = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnviromentalVolume = 1.f;
public:
	UFUNCTION()
	void Save();

	UFUNCTION()
	void Load();
	virtual void Init() override;
	virtual void Shutdown() override;
};
