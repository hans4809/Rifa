// Copyright Epic Games, Inc. All Rights Reserved.

#include "RifaGameMode.h"
#include "RifaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"


ARifaGameMode::ARifaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	/*static ConstructorHelpers::FClassFinder<UGameHUD> GameHUDWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Inventory/WG_GameHUD.WG_GameHUD_C'"));
	if (GameHUDWidgetAsset.Succeeded()) 
	{
		GameHUDWidgetClass = GameHUDWidgetAsset.Class;
	}*/
}

void ARifaGameMode::BeginPlay()
{
	Super::BeginPlay();
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GameInstanceReference = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}


void ARifaGameMode::PlayerDie(ARifaCharacter* Player)
{
	Player->bIsDied = true;
}

void ARifaGameMode::PlayerRespawn(ARifaCharacter* Player)
{
	Player->bIsDied = false;
	if (!(GameInstanceReference->SavePosition == FVector(0, 0, 0))) 
	{
		Player->SetActorLocation(GameInstanceReference->SavePosition);
	}
	else 
	{
		Player->SetActorLocation(FindPlayerStart(Player->GetController())->GetActorLocation());
	}
}
