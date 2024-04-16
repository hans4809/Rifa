// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/SphereComponent.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "Widget/PickupText.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIOCOMPONENT"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETCOMPONENT"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);
	AudioComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetupAttachment(RootComponent);

	Trigger->SetSphereRadius(200.f);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	static ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Script/Engine.SoundWave'/Game/Sounds/SFX/Char_Interact_Get.Char_Interact_Get'"));
	if (Sound.Succeeded()) 
	{
		AudioComponent->Sound = Sound.Object;
	}
	AudioComponent->bAutoActivate = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Inventory/WG_PickupText.WG_PickupText_C'"));
	if (UW.Succeeded()) 
	{
		PickupTextClass = UW.Class;
		WidgetComponent->SetWidgetClass(PickupTextClass);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetDrawSize(FVector2D(50, 50));
	}
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::EndCharacterOverlap);
	WidgetComponent->SetVisibility(false);
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		WidgetComponent->SetVisibility(true);
		bIsInRange = true;
	}
}

void AInteractableActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		WidgetComponent->SetVisibility(false);
		bIsInRange = false;
	}
}

