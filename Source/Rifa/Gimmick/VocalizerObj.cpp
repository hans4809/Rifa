// Fill out your copyright notice in the Description page of Project Settings.


#include "VocalizerObj.h"
#include "Kismet/GameplayStatics.h"
#include "Vocalizer.h"
#include "Containers/Queue.h"
#include "Components/AudioComponent.h"
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

	vocalizerInterval = 2.f;
	speed = 2.f;
	
	if(isPhysicCollision)
		staticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	else
		staticMesh->SetCollisionProfileName(TEXT("SoundZone"));

	soundDuration = soundToPlay->GetDuration();

	world = GetWorld();
	player = world->GetFirstPlayerController()->GetPawn();
	if (GetDistanceTo(player) < triggerSphere->GetScaledSphereRadius())
		isActive = true;
	else
		isActive = false;
	if (GetDistanceTo(player) < vocalizerVisibleSphere->GetScaledSphereRadius())
		isVocalizer = true;
	else
		isVocalizer = false;
}

void AVocalizerObj::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	triggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AVocalizerObj::OnCharacterOverlap_SoundZone);
	triggerSphere->OnComponentEndOverlap.AddDynamic(this, &AVocalizerObj::EndCharacterOverlap_SoundZone);
	vocalizerVisibleSphere->OnComponentBeginOverlap.AddDynamic(this, &AVocalizerObj::OnCharacterOverlap_VocalizerVisibleZone);
	vocalizerVisibleSphere->OnComponentEndOverlap.AddDynamic(this, &AVocalizerObj::EndCharacterOverlap_VocalizerVisibleZone);
}

void AVocalizerObj::TimeCheck()
{
	if (timeDeltaTime_Sound >= soundInterval)
	{
		SoundPlay();
		timeDeltaTime_Sound = 0;
	}
	if (timeDeltaTime_Vocalizer >= vocalizerInterval)
	{
		SoundWave();
		timeDeltaTime_Vocalizer = 0;
	}
}

void AVocalizerObj::SoundPlay()
{
	if (soundToPlay && isActive)
	{
		UAudioComponent* audio = UGameplayStatics::SpawnSoundAtLocation(this, soundToPlay, GetActorLocation());
		audio->OnAudioFinished.AddDynamic(this, &AVocalizerObj::SoundEnd);
		audioComponent.Enqueue(audio);
	}
}

void AVocalizerObj::SoundWave()
{
	if (soundToPlay && isVocalizer)
	{
		AVocalizer* _vocalizer = world->SpawnActor<AVocalizer>(AVocalizer::StaticClass(), GetActorLocation(), FRotator(0));
		_vocalizer->minOpacity = this->minOpacity;
		_vocalizer->maxOpacity = this->maxOpacity;
		_vocalizer->vocalizerColor = this->vocalizerColor;
		_vocalizer->maxSize = vocalizerSphere->GetScaledSphereRadius();
		_vocalizer->speed = this->speed;
		_vocalizer->MoveStart();
	}
}

void AVocalizerObj::SoundOn()
{
	isActive = true;
}

void AVocalizerObj::SoundOff()
{
	isActive = false;

	UAudioComponent* audio;
	while (audioComponent.Dequeue(audio))
	{
		if (audio)
		{
			audio->Stop();
			audio->DestroyComponent();
		}
	}
}

void AVocalizerObj::SoundEnd()
{
	if(isActive)
		audioComponent.Pop();
}

void AVocalizerObj::OnCharacterOverlap_SoundZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SoundOn();
	SoundPlay();
}

void AVocalizerObj::EndCharacterOverlap_SoundZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SoundOff();
	timeDeltaTime_Sound = 0;
}

void AVocalizerObj::OnCharacterOverlap_VocalizerVisibleZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	isVocalizer = true;
	SoundWave();
}

void AVocalizerObj::EndCharacterOverlap_VocalizerVisibleZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	isVocalizer = false;
	timeDeltaTime_Vocalizer = 0;
}

// Called every frame
void AVocalizerObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isActive)
		timeDeltaTime_Sound += DeltaTime;
	if(isVocalizer)
		timeDeltaTime_Vocalizer += DeltaTime;
	TimeCheck();
}