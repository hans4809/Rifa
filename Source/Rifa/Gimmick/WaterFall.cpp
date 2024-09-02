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
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	WaterFall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterFall"));
	TopTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TopTrigger"));
	BottomTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomTrigger"));
	RideUpStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RideUpStartPoint"));
	RideUpEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RideUpEndPoint"));
	RideDownStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RideDownStartPoint"));
	RideDownEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RideDownEndPoint"));
	TopEndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TopEndPoint"));

	RootComponent = WaterFall;
	Sound->SetupAttachment(RootComponent);
	TopTrigger->SetupAttachment(RootComponent);
	BottomTrigger->SetupAttachment(RootComponent);
	RideUpStartPoint->SetupAttachment(BottomTrigger);
	RideUpEndPoint->SetupAttachment(TopTrigger);
	RideDownStartPoint->SetupAttachment(TopTrigger);
	RideDownEndPoint->SetupAttachment(BottomTrigger);
	TopEndPoint->SetupAttachment(TopTrigger);

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

	if (bIsWaterFallActive == true)
	{
		TopTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFall::OnCharacterTopOverlap);
		TopTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFall::EndCharacterTopOverlap);
		BottomTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterFall::OnCharacterBottomOverlap);
		BottomTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaterFall::EndCharacterBottomOverlap);
	}
	else
	{
		RideUpStartPoint->DestroyComponent();
		RideUpEndPoint->DestroyComponent();
		TopEndPoint->DestroyComponent();
		RideDownStartPoint->DestroyComponent();
		RideDownEndPoint->DestroyComponent();
		TopTrigger->DestroyComponent();
		BottomTrigger->DestroyComponent();
	}
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
			Character->bCanRideUpWaterFall = true;
			Character->WaterFallRotation = GetActorRotation();
			Character->RideStartVector = RideUpStartPoint->GetComponentLocation();
			Character->RideEndVector = RideUpEndPoint->GetComponentLocation();
			Character->WaterFallTopVector = TopEndPoint->GetComponentLocation();
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
			Character->RideStartVector = RideDownStartPoint->GetComponentLocation();
			Character->RideEndVector = RideDownEndPoint->GetComponentLocation();
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

