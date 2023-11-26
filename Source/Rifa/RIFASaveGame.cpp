// Fill out your copyright notice in the Description page of Project Settings.


#include "RIFASaveGame.h"
#include "MyGameInstance.h"

URIFASaveGame::URIFASaveGame()
{
	SavePosition = FVector();
	ItemMap = TMap<Item, bool>();
	SaveSlotName = "";
	SaveIndex = 0;
	SoundTrack = "";
}