// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScript/MainMenuLevelScriptActor.h"
#include "Widget/RifaMainHUD.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/BGMSoundActor.h"
#include "Components/AudioComponent.h"
#include "Widget/GameHUD.h"

AMainMenuLevelScriptActor::AMainMenuLevelScriptActor()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUDWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_RifaMainHUD.WG_RifaMainHUD_C'"));
	if (MainHUDWidget.Succeeded())
	{
		MainHUDWidgetClass = MainHUDWidget.Class;
	}
}

void AMainMenuLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(MainHUDWidgetClass))
	{
		GameHUDWidgetAsset->CloseWidget();
		MainHUDWidgetAsset = Cast<URifaMainHUD>(CreateWidget(GetWorld(), MainHUDWidgetClass));
		if (MainHUDWidgetAsset)
		{
			MainHUDWidgetAsset->Init();
		}
	}
	Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(FInputModeUIOnly());
	Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->bShowMouseCursor = true;
	if (BGMActor->GetAudioComponent()->IsPlaying())
	{
		BGMActor->Stop();
	}
	if (IsValid(BGMActor))
	{
		BGMActor->Play();
		BGMActor->GetAudioComponent()->FadeIn(0.1f);
	}
}
