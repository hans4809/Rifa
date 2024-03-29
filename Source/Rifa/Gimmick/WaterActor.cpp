// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterActor.h"
#include "Components/BoxComponent.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "Data/MyGameInstance.h"
#include "Components/AudioComponent.h"

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

void AWaterActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UMyGameInstance* RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (RifaGameInstance->bCanSwim)
		{
			CharacterReference->bCanSwim = true;
			if (!CharacterReference->bIsSwimming) 
			{
				PickupTextReference->AddToViewport();
			}
		}
		FTimerHandle OverlapHandle;
		GetWorld()->GetTimerManager().SetTimer(OverlapHandle, this, &AWaterActor::CharacterOverlapping, 0.1f, true);
	}

}

void AWaterActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UMyGameInstance* RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (RifaGameInstance->bCanSwim)
		{
			CharacterReference->bCanSwim = false;
			PickupTextReference->RemoveFromParent();
		}
	}
}

void AWaterActor::CharacterOverlapping()
{
	if (IsOverlappingActor(CharacterReference))
	{
		if (CharacterReference->bIsSwimming && PickupTextReference->IsInViewport() == true)
		{
			PickupTextReference->RemoveFromParent();
		}
	}

}
