// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelTransform.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelTransform::ALevelTransform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = Trigger;
	Trigger->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevelTransform::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelTransform::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelTransform::OnCharacterOverlap);
}

void ALevelTransform::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARifaCharacter* character = Cast<ARifaCharacter>(OtherActor);
	if (character)
		UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

// Called every frame
void ALevelTransform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}