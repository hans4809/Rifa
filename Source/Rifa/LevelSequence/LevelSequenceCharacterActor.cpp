// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceCharacterActor.h"
#include "Data/MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ALevelSequenceCharacterActor::ALevelSequenceCharacterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;

	CurrentCharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CurrentCharacterMesh->SetupAttachment(RootComponent);
	CurrentCharacterMesh->SetCollisionProfileName(TEXT("NoCollision"));

	CurrentHairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	CurrentHairMesh->SetupAttachment(RootComponent);
	CurrentHairMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ALevelSequenceCharacterActor::CharacterApperanceChanged()
{
	CurrentCharacterMesh->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[RifaGameInstance->ECurrentCharacterMaterial]);
	CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]);

	if (RifaGameInstance->ECurrentCharacterHairPart == EHairPartsItem::Default)
	{
		CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[RifaGameInstance->ECurrentCharacterMaterial]); 
		CurrentHairMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}
	else
	{
		CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]->GetMaterials()[0].MaterialInterface);
		CurrentHairMesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	}

	const UEnum* HairPartEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.EHairPartsItem"));
	FString EnumMetaData = HairPartEnum->GetDisplayNameTextByValue((int)CharacterReference->ECurrentCharacterHairPart).ToString();
	if (EnumMetaData.Contains(TEXT("Default")))
	{
		CurrentHairMesh->AttachToComponent(CurrentCharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_Default"));
	}
	else
	{
		CurrentHairMesh->AttachToComponent(CurrentCharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_HairParts"));
	}
}

// Called when the game starts or when spawned
void ALevelSequenceCharacterActor::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentHairMesh->AttachToComponent(CurrentCharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket"));
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(RifaGameInstance))
	{
		CurrentCharacterMesh->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[RifaGameInstance->ECurrentCharacterMaterial]);
		CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]);
		if (RifaGameInstance->ECurrentCharacterHairPart == EHairPartsItem::Default)
		{
			CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[RifaGameInstance->ECurrentCharacterMaterial]);
		}
		else
		{
			CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]->GetMaterials()[0].MaterialInterface);
		}
	}

	const UEnum* HairPartEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.EHairPartsItem"));
	FString EnumMetaData = HairPartEnum->GetDisplayNameTextByValue((int)CharacterReference->ECurrentCharacterHairPart).ToString();
	if (EnumMetaData.Contains(TEXT("Default")))
	{
		CurrentHairMesh->AttachToComponent(CurrentCharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_Default"));
	}
	else
	{
		CurrentHairMesh->AttachToComponent(CurrentCharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_HairParts"));
	}
}

// Called every frame
void ALevelSequenceCharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

