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
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETCOMPONENT"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
	Trigger->SetupAttachment(Mesh);
	WidgetComponent->SetupAttachment(Mesh);

	static ConstructorHelpers::FClassFinder<UUserWidget> WC(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_LeftClick.WG_LeftClick_C'"));
	if (WC.Succeeded())
	{
		WidgetClass = WC.Class;
		WidgetComponent->SetWidgetClass(WidgetClass);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetDrawSize(FVector2D(71.25f, 61.25f));
	}
	Mesh->SetCollisionProfileName(TEXT("WaterBodyCollision"));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AWaterActor::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWaterActor::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AWaterActor::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	WidgetComponent->SetVisibility(false);
}

// Called every frame
void AWaterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
				if (!CharacterReference->bIsSwimming && !CharacterReference->GetCharacterMovement()->IsFalling())
				{
					WidgetComponent->SetVisibility(true);
				}
			}
		}
		FTimerHandle OverlapHandle;
		GetWorld()->GetTimerManager().SetTimer(OverlapHandle, this, &AWaterActor::CharacterOverlapping, 0.1f, true);
	}

}

void AWaterActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UMyGameInstance* RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (RifaGameInstance->bCanSwim)
		{
			CharacterReference->bCanSwim = false;
			WidgetComponent->SetVisibility(false);
			//PickupTextReference->RemoveFromParent();
		}
	}
}

void AWaterActor::CharacterOverlapping()
{
	if (IsOverlappingActor(CharacterReference)&& WidgetComponent->IsVisible())
	{
		if (CharacterReference->bIsSwimming)
		{
			//PickupTextReference->RemoveFromParent();
			WidgetComponent->SetVisibility(false);
		}
	}

}
