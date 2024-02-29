// Fill out your copyright notice in the Description page of Project Settings.


#include "Vocalizer.h"

// Sets default values
AVocalizer::AVocalizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = staticMesh;

	staticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>sphereMesh(TEXT("/Script/Engine.StaticMesh'/Game/sphere.sphere'"));
	if (sphereMesh.Succeeded() && sphereMesh.Object != nullptr) staticMesh->SetStaticMesh(sphereMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial>vocalizerMesh(TEXT("/Script/Engine.Material'/Game/VocalizerMaterial.VocalizerMaterial'"));
	if (vocalizerMesh.Succeeded() && vocalizerMesh.Object != nullptr) staticMesh->SetMaterial(0, vocalizerMesh.Object);

	isStart = false;
	SetActorScale3D(FVector(0));
}

// Called when the game starts or when spawned
void AVocalizer::BeginPlay()
{
	Super::BeginPlay();
}

void AVocalizer::MoveStart()
{
	staticMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), vocalizerColor);
	staticMesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), maxOpacity);

	isStart = true;
	scale = 0;
}

void AVocalizer::Move()
{
	scale += speed;
	if (scale > maxSize)
		Destroy();
	SetActorScale3D(FVector(scale));
	staticMesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), FMath::Lerp(minOpacity, maxOpacity, 2 / ((scale / maxSize) + 1) - 1));
}

// Called every frame
void AVocalizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isStart)
		Move();
}