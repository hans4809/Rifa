// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Widget/RifaMainHUD.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/BGMSoundActor.h"
#include "Components/AudioComponent.h"

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
