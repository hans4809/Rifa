// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterActor.h"
#include "Components/BoxComponent.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "Data/MyGameInstance.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWaterActor::AWaterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETCOMPONENT"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
	Trigger->SetupAttachment(Mesh);

	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Mesh->SetCollisionProfileName(TEXT("WaterBodyCollision"));

	//WidgetComponent->SetupAttachment(Mesh);

	/*static ConstructorHelpers::FClassFinder<UUserWidget> WC(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_LeftClick.WG_LeftClick_C'"));
	if (WC.Succeeded())
	{
		WidgetClass = WC.Class;
		WidgetComponent->SetWidgetClass(WidgetClass);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetDrawSize(FVector2D(71.25f, 61.25f));
	}*/

}

// Called when the game starts or when spawned
void AWaterActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Trigger))
	{
		if(Trigger->OnComponentBeginOverlap.IsBound())
			Trigger->OnComponentBeginOverlap.Clear();
		if(Trigger->OnComponentEndOverlap.IsBound())
			Trigger->OnComponentEndOverlap.Clear();

		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterActor::OnCharacterOverlap);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &AWaterActor::EndCharacterOverlap);
	}

	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//WidgetComponent->SetVisibility(false);
}

void AWaterActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UMyGameInstance* RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (RifaGameInstance->bCanSwim)
		{
			if (IsValid(CharacterReference))
			{
				CharacterReference->bCanSwim = true;
				CharacterReference->SwimHeight = GetActorLocation().Z;
			}
		}
	}
}

void AWaterActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UMyGameInstance* RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (RifaGameInstance->bCanSwim)
		{
			if (IsValid(CharacterReference))
			{
				CharacterReference->bCanSwim = false;
			}
		}
	}
}
