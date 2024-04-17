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
	WaterFallBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WaterFallBox"));
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	WaterFall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterFall"));
	TopTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TopTrigger"));
	BottomTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomTrigger"));
	BottomEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BottomEndPoint"));
	TopStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TopStartPoint"));

	RootComponent = WaterFall;
	WaterFallBox->SetupAttachment(RootComponent);
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

	static ConstructorHelpers::FClassFinder<UUserWidget> WaterFallWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_WaterFallWidget.WG_WaterFallWidget_C'"));
	if (WaterFallWidget.Succeeded())
	{
		WaterFallWidgetClass = WaterFallWidget.Class;
	}
	WaterFallBox->SetCollisionProfileName(TEXT("WaterBodyCollision"));
	TopTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BottomTrigger->SetCollisionProfileName(TEXT("Trigger"));
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

