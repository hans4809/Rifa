// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/Zeolite.h"
#include "Components/SphereComponent.h"
#include "Widget/DialogComponent.h"
#include "Widget/PickupText.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

// Sets default values
AZeolite::AZeolite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	DialogComponent = CreateDefaultSubobject<UDialogComponent>(TEXT("DialogComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);
	WidgetComponent->SetupAttachment(RootComponent);

	Trigger->SetSphereRadius(150.f);
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WC(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Inventory/WG_PickupText.WG_PickupText_C'"));
	if (WC.Succeeded()) 
	{
		PickupTextClass = WC.Class;
		WidgetComponent->SetWidgetClass(PickupTextClass);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetDrawSize(FVector2D(50, 50));
	}


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/artifacts/bisuk_bisuk.bisuk_bisuk'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
		Mesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> WC2(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/DialogSystem/WG_DialogWidget.WG_DialogWidget_C'"));
	if (WC2.Succeeded())
	{
		DialogComponent->DialogWidgetClass = WC2.Class;
	}
}

// Called when the game starts or when spawned
void AZeolite::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		PickupTextReference->PickupText = FString(TEXT("Press E"));
		PickupTextReference->PickupActor = this;
		if (IsValid(PickupTextReference))
		{
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			/*if (CharacterReference->PickupItem.IsBound()) {
				CharacterReference->PickupItem.Clear();
			}*/
			CharacterReference->NPCTalk.AddDynamic(this, &AZeolite::Dialog);
		}
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AZeolite::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AZeolite::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	WidgetComponent->SetVisibility(false);
}

// Called every frame
void AZeolite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZeolite::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		WidgetComponent->SetVisibility(true);
		IsInRange = true;
	}
}

void AZeolite::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		WidgetComponent->SetVisibility(false);
		IsInRange = false;
	}
}

void AZeolite::Dialog()
{
	if (IsInRange)
	{
		WidgetComponent->SetVisibility(false);
		DialogComponent->OnInterAction(CharacterReference);
	}
}

