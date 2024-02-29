// Copyright Epic Games, Inc. All Rights Reserved.

#include "RifaGameMode.h"
#include "Character/RifaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Widget/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"


ARifaGameMode::ARifaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_GameHUD.WG_GameHUD_C'"));
	if (GameHUDWidget.Succeeded()) 
	{
		GameHUDWidgetClass = GameHUDWidget.Class;
	}
}

void ARifaGameMode::BeginPlay()
{
	Super::BeginPlay();
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GameInstanceReference = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GameInstanceReference))
	{
		if (!GameInstanceReference->LevelSequencePlayerArr[0]) 
		{
			if (IsValid(FirstLevelSequence)) 
			{
				if (IsValid(CharacterReference)) 
				{
					CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
					FTimerHandle LevelSequenceTimer;
					FirstLevelSequence->SequencePlayer->Play();
					GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ARifaGameMode::EndLevelSequence, FirstLevelSequence->SequencePlayer->GetDuration().AsSeconds(), false);

					GameInstanceReference->LevelSequencePlayerArr[0] = true;
				}
				else 
				{
					if (IsValid(GameHUDWidgetClass))
					{
						GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
					}
				}
			}
		}
		else 
		{
			if (IsValid(GameHUDWidgetClass)) 
			{
				GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
			}
		}
	}
}

void ARifaGameMode::EndLevelSequence()
{
	if (IsValid(GameHUDWidgetClass))
	{
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
	}
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
