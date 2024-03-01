// Fill out your copyright notice in the Description page of Project Settings.


#include "FogRange.h"
#include "Components/BoxComponent.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"

// Sets default values
AFogRange::AFogRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetCollisionProfileName(TEXT("SwitchZone"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));
}

// Called when the game starts or when spawned
void AFogRange::BeginPlay()
{
	Super::BeginPlay();
	FogC = Fog->GetComponent();
}

void AFogRange::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFogRange::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AFogRange::EndCharacterOverlap);
}

void AFogRange::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FogC->SetFogDensity(4.f);
}

void AFogRange::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FogC->SetFogDensity(0.f);
}

// Called every frame
void AFogRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

