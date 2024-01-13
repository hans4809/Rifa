// Fill out your copyright notice in the Description page of Project Settings.


#include "RIFASaveGame.h"

URIFASaveGame::URIFASaveGame()
{
	SavePosition = FVector(0, 0, 0);
	ItemMap = TMap<Item, bool>();
	for (int i = 0; i < (int)Item::MaxCount; i++) {
		ItemMap.Add((Item)i, false);
	}
	SaveSlotName = "";
	SaveIndex = 0;
	SoundTrack = "";
}
