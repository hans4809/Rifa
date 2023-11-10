// Fill out your copyright notice in the Description page of Project Settings.


#include "Template_Pickup.h"
#include "Components/SphereComponent.h"
#include "PickupText.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"
#include "MyGameInstance.h"

// Sets default values
ATemplate_Pickup::ATemplate_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Root;
	Trigger->SetupAttachment(Root);
	Mesh->SetupAttachment(Root);
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
	ItemInfo.Item = Cast<AActor>(this);
	ItemInfo.ItemImage = CustomImage;
	ItemInfo.PickupText = CustomPickupText;
	ItemInfo.AcitonText = CustomActionText;
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == RifaGameInstance) return;
	FItemData* ItmeData = RifaGameInstance->GetItemData(0);
	if (ItmeData) {
		TArray<FStringFormatArg> args;

		args.Add(FStringFormatArg((*ItmeData).ItemNum));
		args.Add(FStringFormatArg((*ItmeData).ItemName));
		args.Add(FStringFormatArg((*ItmeData).Instrument));
		args.Add(FStringFormatArg((*ItmeData).Position));
		args.Add(FStringFormatArg((*ItmeData).BGM_1));
		args.Add(FStringFormatArg((*ItmeData).BGM_2));
		args.Add(FStringFormatArg((*ItmeData).BGM_3));
		args.Add(FStringFormatArg((*ItmeData).BGM_4));
		args.Add(FStringFormatArg((*ItmeData).BGM_5));
		args.Add(FStringFormatArg((*ItmeData).BGM_6));
		args.Add(FStringFormatArg((*ItmeData).BGM_7));
		args.Add(FStringFormatArg((*ItmeData).BGM_8));
		FString string = FString::Format(TEXT("ItemNum = {0} ItemName = {1} Instrument = {3} Position = {4}"), args);
		UE_LOG(LogTemp, Warning, TEXT("String : %s"), *string);
	}
	else {
		UE_LOG(LogClass, Warning, TEXT("ItemData doesn't exist."));
	}
	Mesh->SetStaticMesh(CustomStaticMesh);
	if (IsValid(PickupTextClass))
	{
		PickupTextReference = Cast<UPickupText>(CreateWidget(GetWorld(), PickupTextClass));
		if (IsValid(PickupTextReference))
		{
			PickupTextReference->PickupActor = ItemInfo.Item;
			PickupTextReference->PickupText = ItemInfo.PickupText;
			CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (CharacterReference->PickupItem.IsBound()) {
				CharacterReference->PickupItem.Clear();
			}
			CharacterReference->PickupItem.AddDynamic(this, &ATemplate_Pickup::PickupItemEvent);
		}
	}	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATemplate_Pickup::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ATemplate_Pickup::EndCharacterOverlap);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
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
	UE_LOG(LogTemp, Log, TEXT("CharacterOverlapBegin"));
	if (Cast<ARifaCharacter>(OtherActor)) 
	{
		PickupTextReference->AddToViewport();
		IsInRange = true;
	}
}

void ATemplate_Pickup::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("CharacterOverlapEnd"));
	if (Cast<ARifaCharacter>(OtherActor))
	{
		PickupTextReference->RemoveFromParent();
		IsInRange = false;
	}
}

void ATemplate_Pickup::PickupItemEvent()
{
	if (GetActorEnableCollision() && IsInRange) 
	{
		CharacterReference->GetGameHUDReference()->Inventory.Add(ItemInfo);
		PickupTextReference->RemoveFromParent();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		CharacterReference->GetGameHUDReference()->RefreshInventory_C();
	}
}

