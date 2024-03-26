// Fill out your copyright notice in the Description page of Project Settings.


#include "RIFASaveGame.h"

URIFASaveGame::URIFASaveGame()
{
	SavePosition = FVector(0, 0, 0);

	//SoundItemMap = TMap<Item, bool>();
	for (int i = 0; i < (int)EItem::MaxCount; i++) 
	{
		SoundItemHavingMap.Add((EItem)i, false);
		SoundItemOnOffMap.Add((EItem)i, false);
	}
	for(int i = 0; i < (int)ENPCType::MaxCount; i++)
	{
		NPCDialogMap.Add((ENPCType)i, 0);
	}
	BGMIndex = 0;

	bCanFly = false;
	bCanSwim = false;

	FlyItemArr.Init(false, 5);
	SwimItemArr.Init(false, 5);
	LevelSequencePlayerArr.Init(false, 10);

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
	ECurrentCharacterHairPart = EHairPartsItem::Default;
	for (int m = 0; m < (int)ETutorialType::MaxCount; m++) 
	{
		IsTutorialFinishedMap.Add((ETutorialType)m, false);
	}
	CurrentLevelName = TEXT("Island");
	bClearIslandForest = false;
	bClearFieldForest = false;
}
