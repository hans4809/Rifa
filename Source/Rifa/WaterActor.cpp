// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterActor.h"
#include "Components/BoxComponent.h"
#include "PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "RifaCharacter.h"

// Sets default values
AWaterActor::AWaterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
	Trigger->SetupAttachment(Mesh);
	Mesh->SetCollisionProfileName(TEXT("WaterBodyCollision"));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}

void AWaterActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CharacterReference->bCanSwim = true;
	PickupTextReference->AddToViewport();
}

void AWaterActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CharacterReference->bCanSwim = false;
	PickupTextReference->RemoveFromParent();
}

// Called when the game starts or when spawned
void AWaterActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = Cast<AActor>(this);
			PickupTextReference->ViewPortPosition = Trigger->GetComponentLocation() + FVector(0, 0, 50);
			PickupTextReference->PickupText = FString(TEXT("Click LeftMouseButton"));
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			/*if (CharacterReference->PickupItem.IsBound()) {
				CharacterReference->PickupItem.Clear();
			}*/
			//CharacterReference->PickupItem.AddDynamic(this, &ATemplate_Pickup::PickupItemEvent);
		}
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterActor::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AWaterActor::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}

// Called every frame
void AWaterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

