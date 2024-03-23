// Fill out your copyright notice in the Description page of Project Settings.


#include "HairpartItem.h"
#include "Data/MyGameInstance.h"
#include "Character/RifaCharacter.h"
#include "Widget/PickupText.h"
#include "Components/AudioComponent.h"

AHairpartItem::AHairpartItem()
{
	SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_MESH"));
	SKMesh->SetupAttachment(RootComponent);
	Mesh->DestroyComponent();
}

void AHairpartItem::BeginPlay()
{
	if (IsValid(RifaGameInstance))
	{
		ECurrentHairPart = RifaGameInstance->CurrentHairPartsArr[HairPartArrIdx];
		SKMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[ECurrentHairPart]);
		SKMesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[ECurrentHairPart]->GetMaterials()[0].MaterialInterface);
	}
	if (IsValid(PickupTextReference))
	{
		PickupTextReference->PickupActor = Cast<AActor>(this);
		PickupTextReference->PickupText = TEXT("Press E");

		if (IsValid(CharacterReference))
		{
			CharacterReference->PickupItem.AddDynamic(this, &AHairpartItem::PickupCharacterParts);
		}
	}
}

void AHairpartItem::PickupCharacterParts()
{
	if (bIsInRange)
	{
		AudioComponent->Play();
		EHairPartsItem EtempHairPart = ECurrentHairPart;

		ECurrentHairPart = CharacterReference->ECurrentCharacterHairPart;
		RifaGameInstance->CurrentHairPartsArr[HairPartArrIdx] = ECurrentHairPart;

		CharacterReference->ECurrentCharacterHairPart = EtempHairPart;
		RifaGameInstance->ECurrentCharacterHairPart = CharacterReference->ECurrentCharacterHairPart;

		SKMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[ECurrentHairPart]);
		CharacterReference->CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[CharacterReference->ECurrentCharacterHairPart]);

		if (ECurrentHairPart == EHairPartsItem::Default)
		{
			SKMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[ECharacterMaterialItem::Default]);
			CharacterReference->CurrentHairMesh->SetMaterial(0, CharacterReference->CurrentHairMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
		}
		else
		{
			SKMesh->SetMaterial(0, SKMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
			if (CharacterReference->ECurrentCharacterHairPart == EHairPartsItem::Default)
			{
				CharacterReference->CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[CharacterReference->ECurrentCharacterMaterial]);
			}
			else
			{
				CharacterReference->CurrentHairMesh->SetMaterial(0, CharacterReference->CurrentHairMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
			}
		}
		const UEnum* HairPartEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.EHairPartsItem"));
		FString EnumMetaData = HairPartEnum->GetDisplayNameTextByValue((int)CharacterReference->ECurrentCharacterHairPart).ToString();
		if (EnumMetaData.Contains(TEXT("Default")))
		{
			CharacterReference->CurrentHairMesh->AttachToComponent(CharacterReference->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_Default"));
		}
		else
		{
			CharacterReference->CurrentHairMesh->AttachToComponent(CharacterReference->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_HairParts"));
		}
		RifaGameInstance->Save();
	}

}
