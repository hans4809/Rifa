// Fill out your copyright notice in the Description page of Project Settings.


#include "RIFASaveGame.h"

URIFASaveGame::URIFASaveGame()
{
	SavePosition = FVector(0, 0, 0);

	//SoundItemMap = TMap<Item, bool>();
	for (int i = 0; i < (int)Item::MaxCount; i++) 
	{
		SoundItemMap.Add((Item)i, false);
	}

	FlyItemArr.Init(false, 5);
	SwimItemArr.Init(false, 5);
	LevelSequencePlayerArr.Init(false, 7);

	SaveSlotName = "";
	SaveIndex = 0;
	SoundTrack = "";
	for (int j = 0; j < (int)EHairPartsItem::MaxCount; j++)
	{
		CurrentHairPartsArr.Add((EHairPartsItem)j);
	}
	for (int l = 0; l < (int)ECharacterMaterialItem::MaxCount; l++) 
	{
		CurrentMaterialItemArr.Add((ECharacterMaterialItem)l);
	}
	ECurrentCharacterMaterial = ECharacterMaterialItem::Default;
	ECurrentCharacterHairPart = EHairPartsItem::First;
}
