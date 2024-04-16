// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterailItem.h"
#include "Data/MyGameInstance.h"
#include "Character/RifaCharacter.h"
#include "Widget/PickupText.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"

AMaterailItem::AMaterailItem()
{
}

void AMaterailItem::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(RifaGameInstance))
	{
		ECurrentMaterial = RifaGameInstance->CurrentMaterialItemArr[CharacterMaterialArrIdx];
		Mesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[ECurrentMaterial]);
	}

	if (IsValid(CharacterReference))
	{
		CharacterReference->PickupItem.AddDynamic(this, &AMaterailItem::PickupCharacterMaterial);
	}
}

void AMaterailItem::PickupCharacterMaterial()
{
	if (bIsInRange)
	{
		AudioComponent->Play();
		ECharacterMaterialItem ETempMaterial = ECurrentMaterial;

		ECurrentMaterial = CharacterReference->ECurrentCharacterMaterial;
		RifaGameInstance->CurrentMaterialItemArr[CharacterMaterialArrIdx] = ECurrentMaterial;

		CharacterReference->ECurrentCharacterMaterial = ETempMaterial;
		RifaGameInstance->ECurrentCharacterMaterial = CharacterReference->ECurrentCharacterMaterial;

		Mesh->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[ECurrentMaterial]);
		CharacterReference->GetMesh()->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[CharacterReference->ECurrentCharacterMaterial]);

		if (CharacterReference->ECurrentCharacterHairPart == EHairPartsItem::Default)
		{
			CharacterReference->CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[CharacterReference->ECurrentCharacterMaterial]);
		}		
		RifaGameInstance->Save();
		WidgetComponent->SetVisibility(false);
	}
}
