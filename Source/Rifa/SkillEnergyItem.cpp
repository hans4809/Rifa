// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEnergyItem.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASkillEnergyItem::ASkillEnergyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Root;
	Trigger->SetupAttachment(Root);
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ASkillEnergyItem::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASkillEnergyItem::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ASkillEnergyItem::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			//PickupTextReference->PickupActor = ItemInfo.ItemActor;
			PickupTextReference->PickupText = TEXT("Press E");
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (CharacterReference->PickupItem.IsBound()) {
				CharacterReference->PickupItem.Clear();
			}
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
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}

void ASkillEnergyItem::PickupEnergyEvent()
{
	if (GetActorEnableCollision() && IsInRange)
	{
		PickupTextReference->RemoveFromParent();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
