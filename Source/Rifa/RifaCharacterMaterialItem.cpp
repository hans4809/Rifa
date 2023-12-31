// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterMaterialItem.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"

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
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = Cast<AActor>(this);
			PickupTextReference->PickupText = TEXT("Press E");
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			CharacterReference->PickupItem.AddDynamic(this, &ARifaCharacterMaterialItem::PickupCharacterMaterial);
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
		auto TempMaterial = CharacterReference->GetMesh()->GetMaterial(0);
		CharacterReference->GetMesh()->SetMaterial(0, Mesh->GetMaterial(0));
		Mesh->SetMaterial(0, TempMaterial);
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

