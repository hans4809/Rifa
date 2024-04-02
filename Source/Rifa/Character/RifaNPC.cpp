// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaNPC.h"
#include "Components/SphereComponent.h"
#include "Widget/DialogComponent.h"
#include "Widget/PickupText.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifaNPC::ARifaNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	DialogComponent = CreateDefaultSubobject<UDialogComponent>(TEXT("DialogComponent"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));

	Trigger->SetupAttachment(RootComponent);	
	WidgetComponent->SetupAttachment(RootComponent);
	Trigger->SetSphereRadius(150.f);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Inventory/WG_PickupText.WG_PickupText_C'"));
	if (UW.Succeeded())
	{
		PickupTextClass = UW.Class;
		WidgetComponent->SetWidgetClass(PickupTextClass);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetDrawSize(FVector2D(100, 100));
	}
}

// Called when the game starts or when spawned
void ARifaNPC::BeginPlay()
{
	Super::BeginPlay();
	//if (IsValid(PickupTextClass))
	//{
	//	PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
	//	PickupTextReference->PickupText = FString(TEXT("Press E"));
	//	PickupTextReference->PickupActor = this;
	//	if (IsValid(PickupTextReference))
	//	{
	//		CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//		/*if (CharacterReference->PickupItem.IsBound()) {
	//			CharacterReference->PickupItem.Clear();
	//		}*/
	//		CharacterReference->NPCTalk.AddDynamic(this, &ARifaNPC::Dialog);
	//	}
	//}
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(CharacterReference))
	{
		CharacterReference->NPCTalk.AddDynamic(this, &ARifaNPC::Dialog);
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaNPC::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARifaNPC::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	WidgetComponent->SetVisibility(false);
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
		WidgetComponent->SetVisibility(false);
		if (IsValid(CharacterReference))
		{
			DialogComponent->OnInterAction(CharacterReference);
		}
		/*const UEnum* NPCEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.ENPCType"));
		if(NPCEnum)
		{

			FString EnumMetaData = NPCEnum->GetDisplayNameTextByIndex((int32)ThisNPCType).ToString();
			if (UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance()))
			{
				int32 DialogIndex = GameInstance->NPCDialogMap[ThisNPCType];
				int32 Index = 0;
				if(ThisNPCType == ENPCType::R0)
				{
					Index = FMath::Clamp(DialogIndex, 0, 2);
				}
				else
				{
					Index = FMath::Clamp(DialogIndex, 0, 1);
				}
				FString DialogPath = FString::Printf(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/UI/DialogSystem/DialogTree/NPC/NPC_%s_DialogTree_%d.NPC_%s_DialogTree_%d'"), *EnumMetaData, Index, *EnumMetaData, Index);
				DialogComponent->DialogTree = LoadObject<UBehaviorTree>(nullptr, *DialogPath);
				if (IsValid(DialogComponent->DialogTree))
				{
					DialogComponent->OnInterAction(CharacterReference);
				}
			}
		}*/
	}
}

void ARifaNPC::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		//PickupTextReference->AddToViewport();
		WidgetComponent->SetVisibility(true);
		IsInRange = true;
	}
}

void ARifaNPC::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		//PickupTextReference->RemoveFromParent();
		WidgetComponent->SetVisibility(false);
		IsInRange = false;
	}
}

