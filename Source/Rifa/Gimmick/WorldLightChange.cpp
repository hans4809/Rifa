// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldLightChange.h"
#include "Components/BoxComponent.h"
#include "Character/RifaCharacter.h"

// Sets default values
AWorldLightChange::AWorldLightChange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("START"));
	End = CreateDefaultSubobject<USceneComponent>(TEXT("END"));
	Trigger->SetCollisionProfileName(TEXT("SwitchZone"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

	RootComponent = Trigger;
	End->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWorldLightChange::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldLightChange::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	bIsChangeStart = false;
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWorldLightChange::OnCharacterOverlap);
}

// Called every frame
void AWorldLightChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsChangeStart)
	{
		if (IsValid(Player) && IsValid(End) && IsValid(Light)) 
		{
			float a = FVector::Dist(Player->GetActorLocation(), End->GetComponentLocation()) / MaxDistance;
			if (Distance > a)
			{
				Distance = a;
				Light->SetActorRotation(LightDefaultRotation + FRotator(FMath::Lerp(EndDegree, StartDegree, Distance), 0.0f, 0.0f));
				UE_LOG(LogTemp, Log, TEXT("%f"), FMath::Lerp(StartDegree, EndDegree, Distance));
			}
		}
	}
}

void AWorldLightChange::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<ARifaCharacter>(OtherActor);
	
	MaxDistance = FVector::Dist(Trigger->GetComponentLocation(), End->GetComponentLocation());
	Distance = 1;
	if (IsValid(Light)) 
	{
		LightDefaultRotation = Light->GetActorRotation();
	}
	bIsChangeStart = true;
}

