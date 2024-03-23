// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterFallActorByTriggerBox.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Widget/PickupText.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

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
	TopEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TopEndPoint"));
	BottomEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BottomEndPoint"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));


	RootComponent = Root;
	BottomTrigger->SetupAttachment(RootComponent);
	TopTrigger->SetupAttachment(RootComponent);
	WaterFall->SetupAttachment(RootComponent);
	TopStartPoint->SetupAttachment(TopTrigger);
	BottomStartPoint->SetupAttachment(BottomTrigger);
	TopEndPoint->SetupAttachment(TopTrigger);
	BottomEndPoint->SetupAttachment(BottomTrigger);
	Mesh->SetupAttachment(WaterFall);
	Sound->SetupAttachment(RootComponent);

	BottomTrigger->SetCollisionProfileName(TEXT("Trigger"));
	TopTrigger->SetCollisionProfileName(TEXT("Trigger"));
	Mesh->SetCollisionProfileName(TEXT("WaterBodyCollision"));

	const ConstructorHelpers::FObjectFinder<USoundBase> WaterFallSound(TEXT("/Script/Engine.SoundCue'/Game/Sounds/SFX/Waterfall_Water.Waterfall_Water'"));
	if (WaterFallSound.Succeeded())
	{
		Sound->SetSound(WaterFallSound.Object);
	}
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


	TopTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFallActorByTriggerBox::OnCharacterTopOverlap);
	TopTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFallActorByTriggerBox::EndCharacterTopOverlap);
	/*if (IsValid(Sound->Sound))
	{
		Sound->Play();
	}*/
}

// Called every frame
void AWaterFallActorByTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaterFallActorByTriggerBox::OnCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(CharacterReference = Cast<ARifaCharacter>(OtherActor)))
	{
		if (!CharacterReference->bIsWaterFall)
		{
			BottomPickupTextReference->Init();
			CharacterReference->bCanRideUpWaterFall = true;
			CharacterReference->SwimStartLocation = BottomStartPoint->GetComponentLocation();
			CharacterReference->WaterFallRotation = GetActorRotation();
			CharacterReference->WaterFallEndVector = TopEndPoint->GetComponentLocation();
		}
		else
		{
		}
	}
}

void AWaterFallActorByTriggerBox::EndCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(CharacterReference = Cast<ARifaCharacter>(OtherActor)))
	{
		if(!CharacterReference->bIsWaterFall)
		{
			CharacterReference->SwimStartLocation = FVector::Zero();
		}
		CharacterReference->bCanRideUpWaterFall = false;
		BottomPickupTextReference->CloseWidget();
	}
}

void AWaterFallActorByTriggerBox::OnCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(CharacterReference = Cast<ARifaCharacter>(OtherActor)))
	{
		if (!CharacterReference->bIsSwimming)
		{
			TopPickupTextReference->Init();
			CharacterReference->bCanRideDownWaterFall = true;
			CharacterReference->SwimStartLocation = TopStartPoint->GetComponentLocation();
			CharacterReference->WaterFallRotation = GetActorRotation();
			CharacterReference->WaterFallEndVector = BottomEndPoint->GetComponentLocation();
		}
	}
}

void AWaterFallActorByTriggerBox::EndCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(CharacterReference = Cast<ARifaCharacter>(OtherActor)))
	{
		if (!CharacterReference->bIsWaterFall)
		{

			CharacterReference->SwimStartLocation = FVector::Zero();
		}
		CharacterReference->bCanRideUpWaterFall = false;
		TopPickupTextReference->CloseWidget();
	}
}

