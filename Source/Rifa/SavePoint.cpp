// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePoint.h"
#include "RIFASaveGame.h"
#include "Components/BoxComponent.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SavePosition = CreateDefaultSubobject<USceneComponent>(TEXT("SavePosition"));

	SavePosition->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(TEXT("SavePoint"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASavePoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASavePoint::OnCharacterOverlap);
	Position = SavePosition->GetComponentLocation();
}

void ASavePoint::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Save"));
	SavePlayerData(OtherActor);
}

void ASavePoint::SavePlayerData(AActor* OtherActor)
{
	RifaGameInstance->SavePosition = Position;
	RifaGameInstance->Save();
}