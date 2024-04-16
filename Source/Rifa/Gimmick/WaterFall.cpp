// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/WaterFall.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Character/RifaCharacter.h"
#include "Widget/WaterFallWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWaterFall::AWaterFall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	WaterFall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterFall"));
	TopTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TopTrigger"));
	BottomTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomTrigger"));
	BottomEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BottomEndPoint"));
	TopStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TopStartPoint"));

	RootComponent = WaterFall;
	Mesh->SetupAttachment(RootComponent);
	Sound->SetupAttachment(RootComponent);
	TopTrigger->SetupAttachment(RootComponent);
	BottomTrigger->SetupAttachment(RootComponent);
	BottomEndPoint->SetupAttachment(BottomTrigger);
	TopStartPoint->SetupAttachment(TopTrigger);

	static ConstructorHelpers::FObjectFinder<USoundBase> WaterFallSound(TEXT("/Script/Engine.SoundCue'/Game/Sounds/SFX/Waterfall_Water.Waterfall_Water'"));
	if (WaterFallSound.Succeeded())
	{
		Sound->SetSound(WaterFallSound.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(TEXT("/Script/Engine.StaticMesh'/Game/BluePrint/Gimmick/Waterfall_Collsion.Waterfall_Collsion'"));
	if (MESH.Succeeded())
	{
		Mesh->SetStaticMesh(MESH.Object);
		Mesh->SetRelativeLocationAndRotation(FVector(0, -360.0f, 0), FRotator(0, 0, 0));
		Mesh->SetRelativeScale3D(FVector(1.75f, 1.0f, 1.715f));
		Mesh->SetCollisionProfileName(TEXT("WaterBodyCollision"));
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> WaterFallWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_WaterFallWidget.WG_WaterFallWidget_C'"));
	if (WaterFallWidget.Succeeded())
	{
		WaterFallWidgetClass = WaterFallWidget.Class;
	}
}

// Called when the game starts or when spawned
void AWaterFall::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(WaterFallWidgetClass))
	{
		WaterFallWidgetInstance = CreateWidget<UWaterFallWidget>(GetWorld(), WaterFallWidgetClass);
	}

	TopTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFall::OnCharacterTopOverlap);
	TopTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFall::EndCharacterTopOverlap);
	BottomTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFall::OnCharacterBottomOverlap);
	BottomTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFall::EndCharacterBottomOverlap);
	
}

void AWaterFall::OnCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARifaCharacter* Character = Cast<ARifaCharacter>(OtherActor))
	{
		if (!Character->bIsRideDownWaterFall)
		{
			if (IsValid(WaterFallWidgetClass))
			{
				if (!IsValid(WaterFallWidgetInstance))
				{
					WaterFallWidgetInstance = CreateWidget<UWaterFallWidget>(GetWorld(), WaterFallWidgetClass);
				}
				WaterFallWidgetInstance->Init();
			}
		}
	}
}

void AWaterFall::EndCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARifaCharacter* Character = Cast<ARifaCharacter>(OtherActor))
	{
		WaterFallWidgetInstance->CloseWidget();
		Character->bCanRideUpWaterFall = false;
	}
}

void AWaterFall::OnCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARifaCharacter* Character = Cast<ARifaCharacter>(OtherActor))
	{
		if (!Character->bIsRideUpWaterFall)
		{
			if (IsValid(WaterFallWidgetClass))
			{
				if (!IsValid(WaterFallWidgetInstance))
				{
					WaterFallWidgetInstance = CreateWidget<UWaterFallWidget>(GetWorld(), WaterFallWidgetClass);
				}
				WaterFallWidgetInstance->Init();
			}
			Character->bCanRideDownWaterFall = true;
			Character->WaterFallRotation = GetActorRotation();
			Character->SwimStartLocation = TopStartPoint->GetComponentLocation();
		}
	}
}

void AWaterFall::EndCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARifaCharacter* Character = Cast<ARifaCharacter>(OtherActor))
	{
		WaterFallWidgetInstance->CloseWidget();
		Character->bCanRideDownWaterFall = false;
	}
}

// Called every frame
void AWaterFall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

