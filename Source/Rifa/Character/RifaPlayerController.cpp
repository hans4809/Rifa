// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RifaPlayerController.h"
#include <Widget/GameHUD.h>
#include <LevelScript/IslandLevelScriptActor.h>
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widget/CreditWidget.h"
#include "Widget/GameSettingWidget.h"

ARifaPlayerController::ARifaPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_GameHUD.WG_GameHUD_C'"));
	if (GameHUDWidget.Succeeded())
	{
		GameHUDWidgetClass = GameHUDWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameSettingWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_GameSettingWidget.WG_GameSettingWidget_C'"));
	if (GameSettingWidget.Succeeded())
	{
		GameSettingWidgetClass = GameSettingWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> CreditWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_Credit.WG_Credit_C'"));
	if (CreditWidgetClassFinder.Succeeded())
	{
		CreditWidgetClass = CreditWidgetClassFinder.Class;
	}
}

void ARifaPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (IsValid(GameHUDWidgetClass))
	{
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
		if(IsValid(GameHUDWidgetAsset))
		{
			GameHUDWidgetAsset->Init();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameHUDWidgetAsset is not valid"));
		}
	}

	if (CreditWidgetClass)
	{
		CreditWidgetAsset = CreateWidget<UCreditWidget>(GetWorld(), CreditWidgetClass);
	}

	auto currentLevelScriptActor = GetWorld()->GetLevelScriptActor();

	TArray<AActor*, FDefaultAllocator> levelSequenceActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), levelSequenceActors);

	for(auto actor : levelSequenceActors)
	{
		if (IsValid(actor))
		{
			auto levelSequenceActor = Cast<ALevelSequenceActor>(actor);
			if(IsValid(levelSequenceActor))
			{
				if(levelSequenceActor->SequencePlayer->OnPlay.IsBound())
					levelSequenceActor->SequencePlayer->OnPlay.Clear();
				if(levelSequenceActor->SequencePlayer->OnFinished.IsBound())
					levelSequenceActor->SequencePlayer->OnFinished.Clear();

				levelSequenceActor->SequencePlayer->OnPlay.AddDynamic(this, &ARifaPlayerController::OnStartedLevelSequence);
				levelSequenceActor->SequencePlayer->OnFinished.AddDynamic(this, &ARifaPlayerController::OnFinishedLevelSequence);
			}
		}
	}
}

void ARifaPlayerController::BeginPlay()
{
}

void ARifaPlayerController::Tick(float DeltaTime)
{
}

void ARifaPlayerController::OnStartedLevelSequence()
{
	DisableInput(this);
	auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	if (IsValid(GameHUDWidgetClass) && !IsValid(GameHUDWidgetAsset))
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));

	if (IsValid(GameHUDWidgetAsset))
	{
		GameHUDWidgetAsset->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ARifaPlayerController::OnFinishedLevelSequence()
{
	EnableInput(this);
	auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	if (IsValid(GameHUDWidgetClass) && !IsValid(GameHUDWidgetAsset))
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));

	if (IsValid(GameHUDWidgetAsset))
	{
		GameHUDWidgetAsset->SetVisibility(ESlateVisibility::Visible);
	}
}

void ARifaPlayerController::OnFinishedGame()
{
	if (CreditWidgetAsset)
	{
		CreditWidgetAsset->Init();
	}
}

void ARifaPlayerController::OnPauseGame()
{
	if (IsValid(GameSettingWidgetClass) && !IsValid(GameSettingWidgetAsset))
	{
		GameSettingWidgetAsset = Cast<UGameSettingWidget>(CreateWidget(GetWorld(), GameSettingWidgetClass));
	}

	if (IsValid(GameSettingWidgetAsset))
	{
		GameSettingWidgetAsset->Init();
		GameSettingWidgetAsset->ParentWidget = GameHUDWidgetAsset;
	}
}
