// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterParts.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifaCharacterParts::ARifaCharacterParts()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	//Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Root;
	//Trigger->SetupAttachment(Root);
	Mesh->SetupAttachment(Root);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/RifaCharacters/Test/idletest_hair01.idletest_hair01'"));
	if (SW.Succeeded())
	{
		Mesh->SetStaticMesh(SW.Object);
	}
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ARifaCharacterParts::BeginPlay()
{
	Super::BeginPlay();
	/*Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaCharacterParts::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARifaCharacterParts::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = Cast<AActor>(this);
			PickupTextReference->PickupText = TEXT("Press E");
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			CharacterReference->PickupItem.AddDynamic(this, &ARifaCharacterParts::PickupCharacterParts);
		}
	}*/
}

void ARifaCharacterParts::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}

void ARifaCharacterParts::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->RemoveFromParent();
		IsInRange = false;
	}
}

void ARifaCharacterParts::PickupCharacterParts()
{
	if (GetActorEnableCollision() && IsInRange)
	{
		FName HairSocket(TEXT("hair_socket"));
		PickupTextReference->RemoveFromParent();
		Mesh->AttachToComponent(CharacterReference->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HairSocket);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
// Called every frame
void ARifaCharacterParts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

