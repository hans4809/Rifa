// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceCharacterActor.h"
#include "MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "RifaCharacter.h"
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
		CurrentHairMesh->SetRelativeLocationAndRotation(FVector(2.3f, -2.8f, 15.7f), FRotator(-60.f, 20.f, 0.f));
	}
	else
	{
		CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]->GetMaterials()[0].MaterialInterface);
	}

}

// Called when the game starts or when spawned
void ALevelSequenceCharacterActor::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentHairMesh->AttachToComponent(CurrentCharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket"));
	if (IsValid(RifaGameInstance))
	{
		CurrentCharacterMesh->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[RifaGameInstance->ECurrentCharacterMaterial]);
		CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]);
		if (RifaGameInstance->ECurrentCharacterHairPart == EHairPartsItem::Default)
		{
			CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[RifaGameInstance->ECurrentCharacterMaterial]);
			CurrentHairMesh->SetRelativeLocationAndRotation(FVector(2.3f, -2.8f, 15.7f), FRotator(-60.f, 20.f, 0.f));
		}
		else
		{
			CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[RifaGameInstance->ECurrentCharacterHairPart]->GetMaterials()[0].MaterialInterface);
		}
	}
}

// Called every frame
void ALevelSequenceCharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

