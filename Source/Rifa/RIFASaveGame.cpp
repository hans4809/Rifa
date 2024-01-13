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
	HairPartsMap = TMap<EHairPartsItem, TObjectPtr<USkeletalMesh>>();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH1(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/idletest_hair01.idletest_hair01'"));
	if (MESH1.Succeeded())
	{
		HairPartsMap.Add(EHairPartsItem::First, MESH1.Object);
	}

	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH2(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/idletest_hair01.idletest_hair01'"));
	if (MESH2.Succeeded()) {
		HairPartsMap.Add(EHairPartsItem::Second, MESH2.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH3(TEXT("/Script/Engine.SkeletalMesh'/Game/RifaCharacters/idletest_hair01.idletest_hair01'"));
	if (MESH3.Succeeded()) {
		HairPartsMap.Add(EHairPartsItem::Third, MESH3.Object);
	}*/


	CharacterMaterialMap = TMap<ECharacterMaterialItem, TObjectPtr<UMaterialInterface>>();
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material1(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Default.Default'"));
	if (Material1.Succeeded()) {
		CharacterMaterialMap.Add(ECharacterMaterialItem::Default, Material1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material2(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/White.White'"));
	if (Material2.Succeeded()) {
		CharacterMaterialMap.Add(ECharacterMaterialItem::White, Material2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material3(TEXT("/Script/Engine.Material'/Game/RifaCharacters/Texture/Blue.Blue'"));
	if (Material3.Succeeded()) {
		CharacterMaterialMap.Add(ECharacterMaterialItem::Blue, Material3.Object);
	}
}
