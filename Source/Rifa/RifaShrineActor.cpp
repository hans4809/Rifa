// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaShrineActor.h"

// Sets default values
ARifaShrineActor::ARifaShrineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShrinePart1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShrinePart1"));
	ShrinePart2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShrinePart2"));
	ShrinePart3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShrinePart3"));
	ShrinePart4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShrinePart4"));
	Rock = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rock"));
	Wood = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wood"));
	RootComponent = ShrinePart1;
	ShrinePart2->SetupAttachment(RootComponent);
	ShrinePart3->SetupAttachment(RootComponent);
	ShrinePart4->SetupAttachment(RootComponent);
	Rock->SetupAttachment(RootComponent);
	Wood->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARifaShrineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARifaShrineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

