// Fill out your copyright notice in the Description page of Project Settings.


#include "VocalizerObj.h"
#include "Kismet/GameplayStatics.h"
#include "Vocalizer.h"
#include "Components/SphereComponent.h"

// Sets default values
AVocalizerObj::AVocalizerObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	triggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SOUNDZONE"));
	vocalizerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("VOCALIZERZONE"));
	vocalizerVisibleSphere = CreateDefaultSubobject<USphereComponent>(TEXT("VOCALIZERVISIBLEZONE"));

	RootComponent = staticMesh;
	triggerSphere->SetupAttachment(RootComponent);
	vocalizerSphere->SetupAttachment(RootComponent);
	vocalizerVisibleSphere->SetupAttachment(RootComponent);


	triggerSphere->SetCollisionProfileName(TEXT("SoundZone"));
	vocalizerSphere->SetCollisionProfileName(TEXT("NoCollision"));
	vocalizerVisibleSphere->SetCollisionProfileName(TEXT("SoundZone"));
	staticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	triggerSphere->SetSphereRadius(200.f);
	vocalizerSphere->SetSphereRadius(300.f);
	vocalizerVisibleSphere->SetSphereRadius(400.f);
}

// Called when the game starts or when spawned
void AVocalizerObj::BeginPlay()
{
	Super::BeginPlay();
	
	if(isPhysicCollision)
		staticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	else
		staticMesh->SetCollisionProfileName(TEXT("SoundZone"));

	sphereRadius = triggerSphere->GetScaledSphereRadius();
	soundDuration = soundToPlay->GetDuration();

	world = GetWorld();
	player = world->GetFirstPlayerController()->GetPawn();
	if (GetDistanceTo(player) < sphereRadius)
		isActive = true;
	else
		isActive = false;
}

void AVocalizerObj::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	triggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AVocalizerObj::OnCharacterOverlap);
	triggerSphere->OnComponentEndOverlap.AddDynamic(this, &AVocalizerObj::EndCharacterOverlap);
}

void AVocalizerObj::TimeCheck()
{
	if (timeDeltaTime >= soundInterval)
	{
		SoundPlay();
		timeDeltaTime = 0;
	}
}

void AVocalizerObj::SoundPlay()
{
	if (soundToPlay && isActive)
	{
		volumeSize = (1 - (GetDistanceTo(player) / sphereRadius));
		volumeSize += 0.15f;
		if (volumeSize >= 1)
			volumeSize = 1;
		UE_LOG(LogTemp, Log, TEXT("%f"), volumeSize);
		UGameplayStatics::PlaySoundAtLocation(this, soundToPlay, GetActorLocation(), volumeSize);
		SoundWave();
	}
}

void AVocalizerObj::SoundWave()
{
	//sphereScale = FMath::Lerp(0, 1, timeDeltaTime / soundDuration);
	//vocalizer->SetWorldScale3D(FVector(sphereScale, sphereRadius, sphereScale));
	AVocalizer* _vocalizer = world->SpawnActor<AVocalizer>(AVocalizer::StaticClass(), GetActorLocation(), FRotator(0));
	_vocalizer->minOpacity = this->minOpacity;
	_vocalizer->maxOpacity = this->maxOpacity;
	_vocalizer->vocalizerColor = this->vocalizerColor;
	_vocalizer->maxSize = vocalizerSphere->GetScaledSphereRadius();
	_vocalizer->speed = this->speed;
	_vocalizer->MoveStart();
}

void AVocalizerObj::SoundOn()
{
	isActive = true;
}

void AVocalizerObj::SoundOff()
{
	isActive = false;
	volumeSize = 0;
}

void AVocalizerObj::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SoundOn();
}

void AVocalizerObj::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SoundOff();
}

// Called every frame
void AVocalizerObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeDeltaTime += DeltaTime;
	TimeCheck();
}