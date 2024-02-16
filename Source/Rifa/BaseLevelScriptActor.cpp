// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelScriptActor.h"
#include <Kismet/GameplayStatics.h>
#include "MyGameInstance.h"
#include "RifaCharacter.h"
#include "GameHUD.h"
#include "TutorialWidget.h"

ABaseLevelScriptActor::ABaseLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_GameHUD.WG_GameHUD_C'"));
	if (GameHUD.Succeeded())
	{
		GameHUDWidgetClass = GameHUD.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Tutorial(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_TutorialWidget.WG_TutorialWidget_C'"));
	if (Tutorial.Succeeded())
	{
		TutorialWidgetClass = Tutorial.Class;
	}
}

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstanceReference = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
