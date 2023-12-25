// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaNPC.h"
#include "Components/SphereComponent.h"
#include "DialogComponent.h"
#include "PickupText.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DialogComponent.h"

// Sets default values
ARifaNPC::ARifaNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetSphereRadius(150.f);
	DialogComponent = CreateDefaultSubobject<UDialogComponent>(TEXT("DialogComponent"));
}

// Called when the game starts or when spawned
void ARifaNPC::BeginPlay()
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
			CharacterReference->NPCTalk.AddDynamic(this, &ARifaNPC::Dialog);
		}
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaNPC::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARifaNPC::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}

// Called every frame
void ARifaNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARifaNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARifaNPC::Dialog()
{
	if (IsInRange) 
	{
		DialogComponent->OnInterAction(CharacterReference);
	}
}

void ARifaNPC::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}

void ARifaNPC::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->RemoveFromParent();
		IsInRange = false;
	}
}

