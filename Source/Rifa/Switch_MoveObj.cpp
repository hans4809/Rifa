// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch_MoveObj.h"
#include "Components/BoxComponent.h"
#include "RifaCharacter.h"
#include "Components/InputComponent.h"

// Sets default values
ASwitch_MoveObj::ASwitch_MoveObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	End = CreateDefaultSubobject<USceneComponent>(TEXT("End"));

	RootComponent = Mesh;
	Trigger->SetupAttachment(RootComponent);
	End->SetupAttachment(RootComponent);

	Trigger->SetCollisionProfileName(TEXT("SwitchZone"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));
}

// Called when the game starts or when spawned
void ASwitch_MoveObj::BeginPlay()
{
	Super::BeginPlay();
	startV = Target->GetActorLocation();
	endV = End->GetComponentLocation();
	timeDeltaTime = 0;
	isStart = false;
}

void ASwitch_MoveObj::BeginMove()
{
	if(!isStart)
		isStart = true;
	UE_LOG(LogTemp, Log, TEXT("%f"), timeDeltaTime);
	Target->SetActorLocation(FMath::Lerp(startV, endV, timeDeltaTime / moveTime));
	if (timeDeltaTime >= moveTime)
	{
		GetWorldTimerManager().ClearTimer(fTimeHandler);
	}
}

// Called every frame
void ASwitch_MoveObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isStart)
	{
		timeDeltaTime += DeltaTime;
	}
}

void ASwitch_MoveObj::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASwitch_MoveObj::OnCharacterOverlap);
}

void ASwitch_MoveObj::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isStart) return;
	UE_LOG(LogTemp, Log, TEXT("take"));
	ARifaCharacter* RifaCharacter = Cast<ARifaCharacter>(OtherActor);
	GetWorldTimerManager().SetTimer(fTimeHandler, this, &ASwitch_MoveObj::BeginMove, 0.0005f, true, 1);
}