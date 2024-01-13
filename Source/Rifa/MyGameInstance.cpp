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
}

void UMyGameInstance::Save()
{
	URIFASaveGame* NewPlayerData = NewObject<URIFASaveGame>();
	NewPlayerData->SavePosition = SavePosition;
	NewPlayerData->SoundItemMap = SoundItemMap;
	NewPlayerData->SoundTrack = SoundTrack;
	NewPlayerData->FlyItemArr = FlyItemArr;
	NewPlayerData->SwimItemArr = SwimItemArr;
	NewPlayerData->HairPartsMap = HairPartsMap;
	NewPlayerData->CharacterMaterialMap = CharacterMaterialMap;
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
	SoundItemMap = RIFASaveGame->SoundItemMap;
	SoundTrack = RIFASaveGame->SoundTrack;
	FlyItemArr = RIFASaveGame->FlyItemArr;
	SwimItemArr = RIFASaveGame->SwimItemArr;
	HairPartsMap = RIFASaveGame->HairPartsMap;
	CharacterMaterialMap = RIFASaveGame->CharacterMaterialMap;
	CurrentCharacterMaterial = RIFASaveGame->CurrentCharacterMaterial;
	CurrentHairPart = RIFASaveGame->CurrentHairPart;
}

void UMyGameInstance::Init()
{
	Super::Init();
	Load();
}

void UMyGameInstance::Shutdown()
{
	Save();
	Super::Shutdown();
}
