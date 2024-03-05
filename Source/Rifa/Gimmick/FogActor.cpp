// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/FogActor.h"
#include "Components/BoxComponent.h"
#include <Character/RifaCharacter.h>

// Sets default values
AFogActor::AFogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	RootComponent = Mesh;
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFogActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFogActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor)) 
	{
		Mesh->DestroyComponent();
	}
}

