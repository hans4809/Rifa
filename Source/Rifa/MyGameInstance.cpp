// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "RifaDataTable.h"
#include "RIFASaveGame.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance()
{
	//SoundItemMap = TMap<Item, bool>();
	//for (int i = 0; i < (int)Item::MaxCount; i++) {
	//	SoundItemMap.Add((Item)i, false);
	//}
	//Position = FVector(0, 0, 0);
	//SoundTrack = "";

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH0(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/idletest_hair01.idletest_hair01'"));
	if (MESH0.Succeeded())
	{
		HairPartsMeshMap.Add(EHairPartsItem::Default, MESH0.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH1(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/idletest_hair01.idletest_hair01'"));
	if (MESH1.Succeeded())
	{
		HairPartsMeshMap.Add(EHairPartsItem::First, MESH1.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH2(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/idletest_hair02.idletest_hair02'"));
	if (MESH2.Succeeded())
	{
		HairPartsMeshMap.Add(EHairPartsItem::Second, MESH2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material1(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Default.Default'"));
	if (Material1.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Default, Material1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material2(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/White.White'"));
	if (Material2.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::White, Material2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material3(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Blue.Blue'"));
	if (Material3.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Blue, Material3.Object);
	}
}

bool UMyGameInstance::Save()
{
	URIFASaveGame* NewPlayerData = NewObject<URIFASaveGame>();
	NewPlayerData->SavePosition = SavePosition;
	NewPlayerData->SoundItemMap = SoundItemMap;
	NewPlayerData->SoundTrack = SoundTrack;
	NewPlayerData->FlyItemArr = FlyItemArr;
	NewPlayerData->SwimItemArr = SwimItemArr;
	NewPlayerData->LevelSequencePlayerArr = LevelSequencePlayerArr;
	NewPlayerData->CurrentHairPartsArr = CurrentHairPartsArr;
	NewPlayerData->CurrentMaterialItemArr = CurrentMaterialItemArr;
	NewPlayerData->ECurrentCharacterHairPart = ECurrentCharacterHairPart;
	NewPlayerData->ECurrentCharacterMaterial = ECurrentCharacterMaterial;
	return UGameplayStatics::SaveGameToSlot(NewPlayerData, "RIFASaveFile", 0);
}

void UMyGameInstance::Load()
{
	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
	if (nullptr == RIFASaveGame)
	{
		RIFASaveGame = GetMutableDefault<URIFASaveGame>(); // Gets the mutable default object of a class.
	}
	SavePosition = RIFASaveGame->SavePosition;
	SoundItemMap = RIFASaveGame->SoundItemMap;
	SoundTrack = RIFASaveGame->SoundTrack;
	FlyItemArr = RIFASaveGame->FlyItemArr;
	SwimItemArr = RIFASaveGame->SwimItemArr;
	LevelSequencePlayerArr = RIFASaveGame->LevelSequencePlayerArr;
	CurrentHairPartsArr = RIFASaveGame->CurrentHairPartsArr;
	CurrentMaterialItemArr = RIFASaveGame->CurrentMaterialItemArr;
	ECurrentCharacterMaterial = RIFASaveGame->ECurrentCharacterMaterial;
	ECurrentCharacterHairPart = RIFASaveGame->ECurrentCharacterHairPart;
}

void UMyGameInstance::Init()
{
	Super::Init();
	Load();
}

void UMyGameInstance::Shutdown()
{
	if (!Save()) { Save(); }
	Super::Shutdown();
}
