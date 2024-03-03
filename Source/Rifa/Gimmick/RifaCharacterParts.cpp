// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterParts.h"
#include "Components/SphereComponent.h"
#include "Character/RifaCharacter.h"
#include "Widget/PickupText.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "LevelSequence/LevelSequenceCharacterActor.h"
#include "LevelScript/BaseLevelScriptActor.h"


// Sets default values
ARifaCharacterParts::ARifaCharacterParts()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ARifaCharacterParts::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaCharacterParts::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARifaCharacterParts::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(RifaGameInstance)) 
	{
		ECurrentHairPart = RifaGameInstance->CurrentHairPartsArr[HairPartArrIdx];
		Mesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[ECurrentHairPart]);
		Mesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[ECurrentHairPart]->GetMaterials()[0].MaterialInterface);
	}
	CurrentLevelScriptActorReference = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = Cast<AActor>(this);
			PickupTextReference->PickupText = TEXT("Press E");

			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (IsValid(CharacterReference)) 
			{
				CharacterReference->PickupItem.AddDynamic(this, &ARifaCharacterParts::PickupCharacterParts);
			}
		}
	}


}

// Called every frame
void ARifaCharacterParts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARifaCharacterParts::PickupCharacterParts()
{
	if (GetActorEnableCollision() && IsInRange)
	{
		EHairPartsItem EtempHairPart = ECurrentHairPart;

		ECurrentHairPart = CharacterReference->ECurrentCharacterHairPart;
		RifaGameInstance->CurrentHairPartsArr[HairPartArrIdx] = ECurrentHairPart;

		CharacterReference->ECurrentCharacterHairPart = EtempHairPart;
		RifaGameInstance->ECurrentCharacterHairPart = CharacterReference->ECurrentCharacterHairPart;

		Mesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[ECurrentHairPart]);
		CharacterReference->CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[CharacterReference->ECurrentCharacterHairPart]);

		if (ECurrentHairPart == EHairPartsItem::Default) 
		{
			Mesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[ECharacterMaterialItem::Default]);
			CharacterReference->CurrentHairMesh->SetMaterial(0, CharacterReference->CurrentHairMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
		}
		else 
		{
			Mesh->SetMaterial(0, Mesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
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
	}

}

void ARifaCharacterParts::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		if (IsValid(PickupTextReference)) 
		{
			PickupTextReference->Init();
			IsInRange = true;
		}
	}
}

void ARifaCharacterParts::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		if (IsValid(PickupTextReference)) 
		{
			PickupTextReference->CloseWidget();
			IsInRange = false;
		}
	}
}
