// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Game/RifaGameMode.h"
#include "RIFASaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"

UMyGameInstance::UMyGameInstance()
{
	const UEnum* HairPartEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.EHairPartsItem"));
	const UEnum* CharacterMaterialEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.ECharacterMaterialItem"));
	for (int i = 0; i < (int)EHairPartsItem::MaxCount; i++) 
	{
		if (HairPartEnum) 
		{
			FString EnumMetaData = HairPartEnum->GetDisplayNameTextByValue(i).ToString();
			FString HairPartSkeletonPath = FString::Printf(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/HairParts/SkeletalMesh/SK_HairPart_%s.SK_HairPart_%s'"), *EnumMetaData, *EnumMetaData);
			ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH(*HairPartSkeletonPath);
			if (MESH.Succeeded())
			{
				HairPartsMeshMap.Add((EHairPartsItem)i, MESH.Object);
			}
		}
	}

	for (int j = 0; j < (int)ECharacterMaterialItem::MaxCount; j++) 
	{
		if (CharacterMaterialEnum) 
		{
			FString EnumMetaData = CharacterMaterialEnum->GetDisplayNameTextByValue(j).ToString();

			FString CharacterMaterialPath = FString::Printf(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/%s.%s'"), *EnumMetaData, *EnumMetaData);
			ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial(*CharacterMaterialPath);

			FString HairMaterialPath = FString::Printf(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_%sHair.MI_%sHair'"), *EnumMetaData, *EnumMetaData);
			ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial(*HairMaterialPath);

			if (CharacterMaterial.Succeeded() && HairMaterial.Succeeded())
			{
				CharacterMaterialMap.Add((ECharacterMaterialItem)j, CharacterMaterial.Object);
				HairMaterialMap.Add((ECharacterMaterialItem)j, HairMaterial.Object);
			}
		}
	}

}

void UMyGameInstance::Save()
{
	URIFASaveGame* NewPlayerData = NewObject<URIFASaveGame>();
	NewPlayerData->SavePosition = SavePosition;
	NewPlayerData->SoundItemHavingMap = SoundItemHavingMap;
	NewPlayerData->SoundItemOnOffMap = SoundItemOnOffMap;
	NewPlayerData->SoundTrack = SoundTrack;
	NewPlayerData->BGMIndex = BGMIndex;
	NewPlayerData->FlyItemArr = FlyItemArr;
	NewPlayerData->SwimItemArr = SwimItemArr;
	NewPlayerData->LevelSequencePlayerArr = LevelSequencePlayerArr;
	NewPlayerData->CurrentHairPartsArr = CurrentHairPartsArr;
	NewPlayerData->CurrentMaterialItemArr = CurrentMaterialItemArr;
	NewPlayerData->ECurrentCharacterHairPart = ECurrentCharacterHairPart;
	NewPlayerData->ECurrentCharacterMaterial = ECurrentCharacterMaterial;
	NewPlayerData->IsTutorialFinishedMap = IsTutorialFinishedMap;
	NewPlayerData->bCanFly = bCanFly;
	NewPlayerData->bCanSwim = bCanSwim;
	//NewPlayerData->bCanSwim = true;
	NewPlayerData->CurrentLevelName = CurrentLevelName;
	NewPlayerData->bClearIslandForest = bClearIslandForest;
	NewPlayerData->bClearFieldForest = bClearFieldForest;
	NewPlayerData->NPCDialogMap = NPCDialogMap;
	UGameplayStatics::SaveGameToSlot(NewPlayerData, "RIFASaveFile", 0);
}

void UMyGameInstance::Load()
{
	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
	if (nullptr == RIFASaveGame)
	{
		RIFASaveGame = GetMutableDefault<URIFASaveGame>(); // Gets the mutable default object of a class.
	}
	SavePosition = RIFASaveGame->SavePosition;
	SoundItemHavingMap = RIFASaveGame->SoundItemHavingMap;
	SoundItemOnOffMap = RIFASaveGame->SoundItemOnOffMap;
	SoundTrack = RIFASaveGame->SoundTrack;
	BGMIndex = RIFASaveGame->BGMIndex;
	FlyItemArr = RIFASaveGame->FlyItemArr;
	//SwimItemArr = RIFASaveGame->SwimItemArr;
	for (int i = 0; i < 5; i++)
	{
		SwimItemArr.Add(true);
	}
	NPCDialogMap = RIFASaveGame->NPCDialogMap;
	LevelSequencePlayerArr = RIFASaveGame->LevelSequencePlayerArr;
	CurrentHairPartsArr = RIFASaveGame->CurrentHairPartsArr;
	CurrentMaterialItemArr = RIFASaveGame->CurrentMaterialItemArr;
	ECurrentCharacterMaterial = RIFASaveGame->ECurrentCharacterMaterial;
	ECurrentCharacterHairPart = RIFASaveGame->ECurrentCharacterHairPart;
	IsTutorialFinishedMap = RIFASaveGame->IsTutorialFinishedMap;
	bCanFly = RIFASaveGame->bCanFly;
	//bCanSwim = RIFASaveGame->bCanSwim;
	bCanSwim = true;
	CurrentLevelName = RIFASaveGame->CurrentLevelName;
	bClearIslandForest = RIFASaveGame->bClearIslandForest;
	bClearFieldForest = RIFASaveGame->bClearFieldForest;
	if (CurrentLevelName == TEXT("MainMenu"))
	{
		CurrentLevelName = "Island";
	}
}

void UMyGameInstance::ResetSaveData()
{
	URIFASaveGame* RIFASaveGame = GetMutableDefault<URIFASaveGame>();
	SavePosition = RIFASaveGame->SavePosition;
	NPCDialogMap = RIFASaveGame->NPCDialogMap;
	SoundItemHavingMap = RIFASaveGame->SoundItemHavingMap;
	SoundItemOnOffMap = RIFASaveGame->SoundItemOnOffMap;
	SoundTrack = RIFASaveGame->SoundTrack;
	BGMIndex = RIFASaveGame->BGMIndex;
	FlyItemArr = RIFASaveGame->FlyItemArr;
	SwimItemArr = RIFASaveGame->SwimItemArr;
	LevelSequencePlayerArr = RIFASaveGame->LevelSequencePlayerArr;
	CurrentHairPartsArr = RIFASaveGame->CurrentHairPartsArr;
	CurrentMaterialItemArr = RIFASaveGame->CurrentMaterialItemArr;
	ECurrentCharacterMaterial = RIFASaveGame->ECurrentCharacterMaterial;
	ECurrentCharacterHairPart = RIFASaveGame->ECurrentCharacterHairPart;
	IsTutorialFinishedMap = RIFASaveGame->IsTutorialFinishedMap;
	bCanFly = RIFASaveGame->bCanFly;
	bCanSwim = RIFASaveGame->bCanSwim;
	CurrentLevelName = RIFASaveGame->CurrentLevelName;
	bClearIslandForest = RIFASaveGame->bClearIslandForest;
	bClearFieldForest = RIFASaveGame->bClearFieldForest;
	CurrentLevelName = RIFASaveGame->CurrentLevelName;
}

void UMyGameInstance::Init()
{
	Super::Init();
	Load();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
	Save();
}
