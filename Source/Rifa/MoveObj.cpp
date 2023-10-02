// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveObj.h"

// Sets default values
AMoveObj::AMoveObj()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	End = CreateDefaultSubobject<USceneComponent>(TEXT("End"));

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AMoveObj::BeginPlay()
{
	Super::BeginPlay();

	isFirst = true;
	startV = GetActorLocation();
	endV = End->GetComponentLocation();
	GetWorldTimerManager().SetTimer(fTimeHandler, this, &AMoveObj::BeginMove, 0.01f, true, waitTime);
}

// Called every frame
void AMoveObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeDeltaTime += DeltaTime;
}

void AMoveObj::BeginMove() {
	if (isFirst)
	{
		timeDeltaTime = 0;
		isFirst = false;
	}
	SetActorLocation(FMath::Lerp(startV, endV, timeDeltaTime / moveTime));

	// 타이머가 끝나면
	if (timeDeltaTime >= moveTime) {
		timeDeltaTime = 0;
		isFirst = true;
		GetWorldTimerManager().ClearTimer(fTimeHandler);
		GetWorldTimerManager().SetTimer(fTimeHandler, this, &AMoveObj::EndMove, 0.0005f, true, waitTime);
	}
}

void AMoveObj::EndMove() {
	if (isFirst)
	{
		timeDeltaTime = 0;
		isFirst = false;
	}
	SetActorLocation(FMath::Lerp(endV, startV, timeDeltaTime / moveTime));

	// 타이머가 끝나면
	if (timeDeltaTime >= moveTime) {
		timeDeltaTime = 0;
		isFirst = true;
		GetWorldTimerManager().ClearTimer(fTimeHandler);
		GetWorldTimerManager().SetTimer(fTimeHandler, this, &AMoveObj::BeginMove, 0.0005f, true, waitTime);
	}
}