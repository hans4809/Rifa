// Fill out your copyright notice in the Description page of Project Settings.


#include "Template_Pickup.h"
#include "Components/SphereComponent.h"
#include "PickupText.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"
#include "MyGameInstance.h"
#include "IslandLevelScriptActor.h"
#include "NiagaraComponent.h"

// Sets default values
ATemplate_Pickup::ATemplate_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));

	RootComponent = Root;
	Trigger->SetupAttachment(Root);
	Mesh->SetupAttachment(Root);
	Particle->SetupAttachment(Root);
	Particle->SetAsset(LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_item.VFX_item'")));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	//GameHUDReference = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor())->GameHUDWidget;
	/*static ConstructorHelpers::FClassFinder<UPickupText> PickupTextAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Inventory/WG_PickupText.WG_PickupText_C'"));
	if (PickupTextAsset.Succeeded())
	{
		PickupTextClass = PickupTextAsset.Class;
	}*/
	//static ConstructorHelpers::FClassFinder<ARifaCharacter> ChracterAsset(TEXT("/Script/Engine.Blueprint'/Game/RifaCharacters/BluePrints/BP_RifaCharacter.BP_RifaCharacter_C'"));
}

// Called when the game starts or when spawned
void ATemplate_Pickup::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (RifaGameInstance->SoundItemHavingMap[(Item)ItemIndex]) 
	{
		Destroy();
		return;
	}
	else 
	{
		ItemInfo.ItemActor = Cast<AActor>(this);
		ItemInfo.ItemImage = CustomImage;
		ItemInfo.ItemName = CustomItemName;
		Mesh->SetStaticMesh(CustomStaticMesh);
		if (IsValid(PickupTextClass))
		{
			PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
			if (IsValid(PickupTextReference))
			{
				PickupTextReference->PickupActor = ItemInfo.ItemActor;
				PickupTextReference->ViewPortPosition = ItemInfo.ItemActor->GetActorLocation() + FVector(0, 0, 50);
				PickupTextReference->PickupText = ItemInfo.ItemName;
				CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				/*if (CharacterReference->PickupItem.IsBound()) {
					CharacterReference->PickupItem.Clear();
				}*/
				CharacterReference->PickupItem.AddDynamic(this, &ATemplate_Pickup::PickupItemEvent);
			}
		}
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATemplate_Pickup::OnCharacterOverlap);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &ATemplate_Pickup::EndCharacterOverlap);
	}
}

void ATemplate_Pickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


// Called every frame
void ATemplate_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATemplate_Pickup::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor)) 
	{
		PickupTextReference->Init();
		IsInRange = true;
	}
}

void ATemplate_Pickup::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->CloseWidget();
		IsInRange = false;
	}
}
	
void ATemplate_Pickup::PickupItemEvent()
{
	if (GetActorEnableCollision() && IsInRange) 
	{
		RifaGameInstance->SoundItemHavingMap[(Item)ItemIndex] = true;
		//RifaGameInstance->Save();
		PickupTextReference->CloseWidget();
		Destroy();
	}
}

