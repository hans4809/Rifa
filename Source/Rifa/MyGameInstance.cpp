// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "RifaDataTable.h"
#include "RIFASaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"

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

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial1(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Default.Default'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial1(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_DefaultHair.MI_DefaultHair'"));
	if (CharacterMaterial1.Succeeded() && HairMaterial1.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Default, CharacterMaterial1.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::Default, HairMaterial1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial2(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/White.White'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial2(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_WhiteHair.MI_WhiteHair'"));
	if (CharacterMaterial2.Succeeded() && HairMaterial2.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::White, CharacterMaterial2.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::White, HairMaterial2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial3(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Blue.Blue'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial3(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_BlueHair.MI_BlueHair'"));
	if (CharacterMaterial3.Succeeded() && HairMaterial3.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Blue, CharacterMaterial3.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::Blue, HairMaterial3.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial4(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Red.Red'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial4(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_RedHair.MI_RedHair'"));
	if (CharacterMaterial4.Succeeded() && HairMaterial4.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Red, CharacterMaterial4.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::Red, HairMaterial4.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial5(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Green.Green'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial5(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_GreenHair.MI_GreenHair'"));
	if (CharacterMaterial5.Succeeded() && HairMaterial5.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Green, CharacterMaterial5.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::Green, HairMaterial5.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial6(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Yellow.Yellow'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial6(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_YellowHair.MI_YellowHair'"));
	if (CharacterMaterial6.Succeeded() && HairMaterial6.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Yellow, CharacterMaterial6.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::Yellow, CharacterMaterial6.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial7(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Black.Black'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HairMaterial7(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/RifaCharacters/Texture/MI_BlackHiar.MI_BlackHiar'"));
	if (CharacterMaterial7.Succeeded() && HairMaterial7.Succeeded())
	{
		CharacterMaterialMap.Add(ECharacterMaterialItem::Yellow, CharacterMaterial7.Object);
		HairMaterialMap.Add(ECharacterMaterialItem::Yellow, CharacterMaterial7.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture1(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-WASD.Tutorial-WASD'"));
	if (Texture1.Succeeded()) 
	{
		TutorialImageMap.Add(ETutorialType::Movement, Texture1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture2(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-space.Tutorial-space'"));
	if (Texture2.Succeeded())
	{
		TutorialImageMap.Add(ETutorialType::Jump, Texture2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture3(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-shift.Tutorial-shift'"));
	if (Texture3.Succeeded())
	{
		TutorialImageMap.Add(ETutorialType::Dash, Texture3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture4(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-mouserightclick.Tutorial-mouserightclick'"));
	if (Texture4.Succeeded())
	{
		TutorialImageMap.Add(ETutorialType::Fly, Texture4.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture5(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-mouserightclick.Tutorial-mouserightclick'"));
	if (Texture5.Succeeded())
	{
		TutorialImageMap.Add(ETutorialType::Swim, Texture5.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture6(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-mouserightclick.Tutorial-mouserightclick'"));
	if (Texture6.Succeeded())
	{
		TutorialImageMap.Add(ETutorialType::Swim, Texture6.Object);
	}
}

void UMyGameInstance::Save()
{
	URIFASaveGame* NewPlayerData = NewObject<URIFASaveGame>();
	NewPlayerData->SavePosition = SavePosition;
	NewPlayerData->SoundItemHavingMap = SoundItemHavingMap;
	NewPlayerData->SoundItemOnOffMap = SoundItemOnOffMap;
	NewPlayerData->SoundTrack = SoundTrack;
	NewPlayerData->FlyItemArr = FlyItemArr;
	NewPlayerData->SwimItemArr = SwimItemArr;
	NewPlayerData->LevelSequencePlayerArr = LevelSequencePlayerArr;
	NewPlayerData->CurrentHairPartsArr = CurrentHairPartsArr;
	NewPlayerData->CurrentMaterialItemArr = CurrentMaterialItemArr;
	NewPlayerData->ECurrentCharacterHairPart = ECurrentCharacterHairPart;
	NewPlayerData->ECurrentCharacterMaterial = ECurrentCharacterMaterial;
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
	Save();
}

void UMyGameInstance::Shutdown()
{
	Save();
	Super::Shutdown();
}
