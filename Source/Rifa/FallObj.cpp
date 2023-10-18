// Fill out your copyright notice in the Description page of Project Settings.


#include "FallObj.h"
#include "RifaCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AFallObj::AFallObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFallObj::BeginPlay()
{
	Super::BeginPlay();
	DefaultLocation = GetActorLocation();
	DefaultRotation = GetActorRotation();
	Mesh->SetSimulatePhysics(false);
	isFall = false;
}

void AFallObj::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFallObj::OnCharacterOverlap);
}

void AFallObj::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor) == nullptr)
		return;
	if (isFall)
		return;
	isFall = true;
	UE_LOG(LogTemp, Log, TEXT("take"));
	GetWorldTimerManager().SetTimer(fTimeHandler, this, &AFallObj::FallCount, 0.1f, false, FallTime);
}


void AFallObj::FallCount()
{
	UE_LOG(LogTemp, Log, TEXT("fall"));
	GetWorldTimerManager().ClearTimer(fTimeHandler);
	Mesh->SetSimulatePhysics(true);
	GetWorldTimerManager().SetTimer(fTimeHandler, this, &AFallObj::ResetObj, 0.1f, false, RecoveryTime);
}

void AFallObj::ResetObj()
{
	UE_LOG(LogTemp, Log, TEXT("reset"));
	GetWorldTimerManager().ClearTimer(fTimeHandler);
	Mesh->SetSimulatePhysics(false);
	SetActorLocation(DefaultLocation);
	SetActorRotation(DefaultRotation);
	isFall = false;
}