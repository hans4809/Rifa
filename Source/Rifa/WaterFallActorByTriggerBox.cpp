// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterFallActorByTriggerBox.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "PickupText.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWaterFallActorByTriggerBox::AWaterFallActorByTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BottomTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BottmTrigger"));
	TopTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TopTrigger"));
	WaterFall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterFall"));
	TopStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TopStartPoint"));
	BottomStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BottomStartPoint"));


	RootComponent = Root;
	BottomTrigger->SetupAttachment(RootComponent);
	TopTrigger->SetupAttachment(RootComponent);
	WaterFall->SetupAttachment(RootComponent);
	TopStartPoint->SetupAttachment(WaterFall);
	BottomStartPoint->SetupAttachment(WaterFall);
}

// Called when the game starts or when spawned
void AWaterFallActorByTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(PickupTextClass))
	{
		TopPickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		BottomPickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(TopPickupTextReference)&& IsValid(BottomPickupTextReference))
		{
			TopPickupTextReference->PickupActor = Cast<AActor>(this);
			BottomPickupTextReference->PickupActor = Cast<AActor>(this);
			TopPickupTextReference->ViewPortPosition = TopTrigger->GetComponentLocation() + FVector(0, 0, 50);
			BottomPickupTextReference->ViewPortPosition = BottomTrigger->GetComponentLocation() + FVector(0, 0, 50);
			TopPickupTextReference->PickupText = FString(TEXT("Click LeftMouseButton"));
			BottomPickupTextReference->PickupText = FString(TEXT("Click LeftMouseButton"));
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			/*if (CharacterReference->PickupItem.IsBound()) {
				CharacterReference->PickupItem.Clear();
			}*/
			//CharacterReference->PickupItem.AddDynamic(this, &ATemplate_Pickup::PickupItemEvent);
		}
	}
	BottomTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFallActorByTriggerBox::OnCharacterBottomOverlap);
	BottomTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFallActorByTriggerBox::EndCharacterBottomOverlap);
	BottomTrigger->SetCollisionProfileName(TEXT("Trigger"));

	TopTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFallActorByTriggerBox::OnCharacterTopOverlap);
	TopTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFallActorByTriggerBox::EndCharacterTopOverlap);
	TopTrigger->SetCollisionProfileName(TEXT("Trigger"));
}

// Called every frame
void AWaterFallActorByTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaterFallActorByTriggerBox::OnCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor)) 
	{
		BottomPickupTextReference->Init();
		CharacterReference->bCanRideUpWaterFall = true;
	}
}

void AWaterFallActorByTriggerBox::EndCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		BottomPickupTextReference->CloseWidget();
		CharacterReference->bCanRideUpWaterFall = false;
	}
}

void AWaterFallActorByTriggerBox::OnCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		TopPickupTextReference->Init();
		CharacterReference->bCanRideDownWaterFall = true;
		CharacterReference->SwimStartLocation = TopStartPoint->GetComponentLocation();
	}
}

void AWaterFallActorByTriggerBox::EndCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		TopPickupTextReference->CloseWidget();
		CharacterReference->bCanRideDownWaterFall = false;
		CharacterReference->SwimStartLocation = FVector::Zero();
	}
}

