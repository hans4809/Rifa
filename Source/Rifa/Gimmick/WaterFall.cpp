// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/WaterFall.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AWaterFall::AWaterFall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	WaterFall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterFall"));

	RootComponent = WaterFall;
	Mesh->SetupAttachment(RootComponent);
	Sound->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<USoundBase> WaterFallSound(TEXT("/Script/Engine.SoundCue'/Game/Sounds/SFX/Waterfall_Water.Waterfall_Water'"));
	if (WaterFallSound.Succeeded())
	{
		Sound->SetSound(WaterFallSound.Object);
	}

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(TEXT("/Script/Engine.StaticMesh'/Game/BluePrint/Gimmick/Waterfall_Collsion.Waterfall_Collsion'"));
	if (MESH.Succeeded())
	{
		Mesh->SetStaticMesh(MESH.Object);
	}
	Mesh->SetRelativeLocationAndRotation(FVector(0, -360.0f, 0), FRotator(0, 0, 0));
	Mesh->SetRelativeScale3D(FVector(1.75f, 1.0f, 1.715f));
	Mesh->SetCollisionProfileName(TEXT("WaterBodyCollision"));
}

// Called when the game starts or when spawned
void AWaterFall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterFall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

