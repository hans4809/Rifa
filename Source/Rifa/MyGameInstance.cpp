// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "RifaDataTable.h"
#include "RIFASaveGame.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance()
{
	ItemMap = TMap<Item, bool>();
	for (int i = 0; i < (int)Item::MaxCount; i++) {
		ItemMap.Add((Item)i, false);
	}
	Position = FVector(0, 0, 0);
	SoundTrack = "";
}

void UMyGameInstance::Save()
{
	URIFASaveGame* NewPlayerData = NewObject<URIFASaveGame>();
	NewPlayerData->SavePosition = Position;
	NewPlayerData->ItemMap = ItemMap;
	NewPlayerData->SoundTrack = SoundTrack;

	UGameplayStatics::SaveGameToSlot(NewPlayerData, "RIFASaveFile", 0);
}

void UMyGameInstance::Load()
{
	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
	if (nullptr == RIFASaveGame)
	{
		RIFASaveGame = GetMutableDefault<URIFASaveGame>(); // Gets the mutable default object of a class.
		Position = FVector(0, 0, 0);
		ItemMap = TMap<Item, bool>();
		SoundTrack = "";
	}
	else
	{
		Position = RIFASaveGame->SavePosition;
		ItemMap = RIFASaveGame->ItemMap;
		SoundTrack = RIFASaveGame->SoundTrack;
	}
}

void UMyGameInstance::Init()
{
}
