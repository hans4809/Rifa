// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RifaPlayerController.h"
#include <Widget/GameHUD.h>

ARifaPlayerController::ARifaPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_GameHUD.WG_GameHUD_C'"));
	if (GameHUDWidget.Succeeded())
		GameHUDWidgetClass = GameHUDWidget.Class;
}

void ARifaPlayerController::BeginPlay()
{
	if(IsValid(GameHUDWidgetClass))
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));

	if(IsValid(GameHUDWidgetAsset))
		GameHUDWidgetAsset->Init();
}

void ARifaPlayerController::Tick(float DeltaTime)
{
}
