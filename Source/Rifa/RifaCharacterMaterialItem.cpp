// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterMaterialItem.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "LevelSequenceCharacterActor.h"
#include "BaseLevelScriptActor.h"

// Sets default values
ARifaCharacterMaterialItem::ARifaCharacterMaterialItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ARifaCharacterMaterialItem::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaCharacterMaterialItem::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARifaCharacterMaterialItem::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(RifaGameInstance)) 
	{
		ECurrentMaterial = RifaGameInstance->CurrentMaterialItemArr[CharacterMaterialArrIdx];
		Mesh->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[ECurrentMaterial]);
	}

	RifaGameMode = Cast<ARifaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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
				CharacterReference->PickupItem.AddDynamic(this, &ARifaCharacterMaterialItem::PickupCharacterMaterial);
			}
		}
	}
}

// Called every frame
void ARifaCharacterMaterialItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARifaCharacterMaterialItem::PickupCharacterMaterial()
{
	if (GetActorEnableCollision() && IsInRange)
	{
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
			CharacterReference->CurrentHairMesh->SetRelativeLocationAndRotation(FVector(2.3f, -2.8f, 15.7f), FRotator(-60.f, 20.f, 0.f));
		}
		else
		{
			CharacterReference->CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairPartsMeshMap[CharacterReference->ECurrentCharacterHairPart]->GetMaterials()[0].MaterialInterface);
		}

		if (/*IsValid(RifaGameMode)*/IsValid(CurrentLevelScriptActorReference))
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

void ARifaCharacterMaterialItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}

void ARifaCharacterMaterialItem::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->RemoveFromParent();
		IsInRange = false;
	}
}

