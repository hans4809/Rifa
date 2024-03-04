// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Widget/RifaMainHUD.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/BGMSoundActor.h"
#include "Components/AudioComponent.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUDWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_RifaMainHUD.WG_RifaMainHUD_C'"));
	if(MainHUDWidget.Succeeded())
	{
		MainHUDWidgetClass = MainHUDWidget.Class;
	}
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(MainHUDWidgetClass))
	{
		MainHUDWidgetAsset = Cast<URifaMainHUD>(CreateWidget(GetWorld(), MainHUDWidgetClass));
	}
	MainHUDWidgetAsset->Init();
	Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(FInputModeUIOnly());
	Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->bShowMouseCursor = true;
}
