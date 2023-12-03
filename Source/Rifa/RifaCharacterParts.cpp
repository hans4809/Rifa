// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaCharacterParts.h"
#include "Components/SphereComponent.h"
#include "RifaCharacter.h"
#include "PickupText.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifaCharacterParts::ARifaCharacterParts()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/RifaCharacters/Test/idletest_hair01.idletest_hair01'"));
	if (SW.Succeeded())
	{
		Mesh->SetStaticMesh(SW.Object);
	}
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ARifaCharacterParts::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARifaCharacterParts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

