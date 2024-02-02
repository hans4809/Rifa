// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEnergyItem.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameHUD.h"
#include "Components/SizeBox.h"
#include "NiagaraComponent.h"

// Sets default values
ASkillEnergyItem::ASkillEnergyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);
	Particle->SetupAttachment(RootComponent);

	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetSphereRadius(200.f);
	Particle->SetRelativeRotation(FRotator(90.f, 0, 0));
	PickupTextClass = LoadClass<UPickupText>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Inventory/WG_PickupText.WG_PickupText_C'"));
}

// Called when the game starts or when spawned
void ASkillEnergyItem::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASkillEnergyItem::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ASkillEnergyItem::EndCharacterOverlap);

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(RifaGameInstance)) 
	{
		switch (EnergyFeature)
		{
		case EEnergyFeature::Swim:
			if (RifaGameInstance->SwimItemArr[ThisSkillItemIndex])
			{
				SetActorEnableCollision(false);
				Particle->SetActive(false);
			}
			break;
		case EEnergyFeature::Fly:
			if (RifaGameInstance->FlyItemArr[ThisSkillItemIndex])
			{
				SetActorEnableCollision(false);
				Particle->SetActive(false);
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
		Particle->SetActive(false);
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

