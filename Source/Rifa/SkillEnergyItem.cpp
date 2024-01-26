// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEnergyItem.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameHUD.h"
#include "Components/SizeBox.h"

// Sets default values
ASkillEnergyItem::ASkillEnergyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));
	RootComponent = Root;
	Trigger->SetupAttachment(Root);
	Mesh->SetupAttachment(Root);
	Particle->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASkillEnergyItem::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASkillEnergyItem::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ASkillEnergyItem::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(RifaGameInstance)) 
	{
		switch (EnergyFeature)
		{
		case EEnergyFeature::Swim:
			if (RifaGameInstance->SwimItemArr[ThisSkillItemIndex])
			{
				SetActorEnableCollision(false);
				Particle->DeactivateSystem();
			}
			break;
		case EEnergyFeature::Fly:
			if (RifaGameInstance->FlyItemArr[ThisSkillItemIndex])
			{
				SetActorEnableCollision(false);
				Particle->DeactivateSystem();
			}
			break;
		}
	}

	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = Cast<AActor>(this);
			PickupTextReference->ViewPortPosition = Cast<AActor>(this)->GetActorLocation() + FVector(0, 0, 50);
			PickupTextReference->PickupText = TEXT("Press E");
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			CharacterReference->PickupItem.AddDynamic(this, &ASkillEnergyItem::PickupEnergyEvent);
		}
	}

}

// Called every frame
void ASkillEnergyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillEnergyItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}

void ASkillEnergyItem::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->RemoveFromParent();
		IsInRange = false;
	}
}

void ASkillEnergyItem::PickupEnergyEvent()
{
	if (GetActorEnableCollision() && IsInRange)
	{
		PickupTextReference->RemoveFromParent();
		SetActorEnableCollision(false);
		Particle->DeactivateSystem();
		switch (EnergyFeature)
		{
		case EEnergyFeature::Swim:
			if (CharacterReference->SwimEnergyNum < 5) 
			{
				CharacterReference->SwimEnergyNum++;
				CharacterReference->MaxSwimEnergyPercent += 0.2f;
				RifaGameInstance->SwimItemArr[ThisSkillItemIndex] = true;
				CharacterReference->SwimEnergyPercent = CharacterReference->MaxSwimEnergyPercent;
			}
			break;
		case EEnergyFeature::Fly:
			if (CharacterReference->FlyEnergyNum < 5) 
			{
				CharacterReference->FlyEnergyNum++;
				CharacterReference->MaxFlyEnergyPercent += 0.2f;
				RifaGameInstance->FlyItemArr[ThisSkillItemIndex] = true;
				CharacterReference->FlyEnergyPercent = CharacterReference->MaxFlyEnergyPercent;
			}
			break;
		}
	}
}

