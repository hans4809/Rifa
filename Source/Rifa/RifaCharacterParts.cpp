// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterParts.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "LevelSequenceCharacterActor.h"
#include "BaseLevelScriptActor.h"


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

	RifaGameMode = Cast<ARifaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CurrentLevelScriptActorReference = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (/*IsValid(PickupTextClass)*/IsValid(CurrentLevelScriptActorReference))
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
			CharacterReference->CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[CharacterReference->ECurrentCharacterMaterial]);
		}
		else 
		{
			Mesh->SetMaterial(0, Mesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
			if (CharacterReference->ECurrentCharacterHairPart == EHairPartsItem::Default) 
			{
				
				CharacterReference->CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[CharacterReference->ECurrentCharacterMaterial]);
				CharacterReference->CurrentHairMesh->SetRelativeLocationAndRotation(FVector(2.3f, -2.8f, 15.7f), FRotator(-60.f, 20.f, 0.f));
			}
			else 
			{
				CharacterReference->CurrentHairMesh->SetMaterial(0, CharacterReference->CurrentHairMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
			}
		}

		if (IsValid(RifaGameMode)) 
		{
			/*for (const auto LevelSequenceCharacter : RifaGameMode->LevelSequenceCharacterArr) 
			{
				ALevelSequenceCharacterActor* LevelSequenceCharacterReference = Cast<ALevelSequenceCharacterActor>(LevelSequenceCharacter);
				if (IsValid(LevelSequenceCharacterReference))
				{
					LevelSequenceCharacterReference->CharacterApperanceChanged();
				}
			}*/
			for (const auto LevelSequenceCharacter : CurrentLevelScriptActorReference->LevelSequenceCharacterArr)
			{
				ALevelSequenceCharacterActor* LevelSequenceCharacterReference = Cast<ALevelSequenceCharacterActor>(LevelSequenceCharacter);
				if (IsValid(LevelSequenceCharacterReference))
				{
					LevelSequenceCharacterReference->CharacterApperanceChanged();
				}
			}
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

