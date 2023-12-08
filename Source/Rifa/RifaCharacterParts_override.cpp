// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterParts_override.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"

ARifaCharacterParts_override::ARifaCharacterParts_override()
{
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Trigger->SetupAttachment(Root);
}

void ARifaCharacterParts_override::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaCharacterParts_override::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARifaCharacterParts_override::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = Cast<AActor>(this);
			PickupTextReference->PickupText = TEXT("Press E");
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			CharacterReference->PickupItem.AddDynamic(this, &ARifaCharacterParts_override::PickupCharacterParts);
		}
	}
}
void ARifaCharacterParts_override::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}
 
void ARifaCharacterParts_override::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->RemoveFromParent();
		IsInRange = false;
	}
}

void ARifaCharacterParts_override::PickupCharacterParts()
{
	if (GetActorEnableCollision() && IsInRange)
	{
		FName HairSocket(TEXT("hair_socket"));
		PickupTextReference->RemoveFromParent();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		Trigger->RemoveFromRoot();
		CharacterReference->CurrentHair = this;
		CharacterReference->ChangeHairPart();
	}
}