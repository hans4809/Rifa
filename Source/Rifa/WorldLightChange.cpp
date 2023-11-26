// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldLightChange.h"
#include "Components/BoxComponent.h"

// Sets default values
AWorldLightChange::AWorldLightChange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("START"));
	end = CreateDefaultSubobject<USceneComponent>(TEXT("END"));
	Trigger->SetCollisionProfileName(TEXT("SwitchZone"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

	RootComponent = Trigger;
	end->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWorldLightChange::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldLightChange::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	IsChangeStart = false;
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWorldLightChange::OnCharacterOverlap);
}

// Called every frame
void AWorldLightChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsChangeStart)
	{
		float a = FVector::Dist(player->GetActorLocation(), end->GetComponentLocation()) / MaxDistance;
		if (Distance > a)
			Distance = a;
		light->SetActorRotation(light->GetActorRotation() + FRotator(0.0f, FMath::Lerp(StartDegree, EndDegree, a), 0.0f));
	}
}

void AWorldLightChange::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
	MaxDistance = FVector::Dist(Trigger->GetComponentLocation(), end->GetComponentLocation());
	IsChangeStart = true;
}

