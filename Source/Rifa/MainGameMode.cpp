// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "RifaMainHUD.h"
#include <Kismet/GameplayStatics.h>
#include "BGMSoundActor.h"
#include "SoundManagerInstance.h"
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
	GetGameInstance()->GetSubsystem<USoundManagerInstance>()->BGMSound = Cast<UAudioComponent>(UGameplayStatics::GetActorOfClass(GetWorld(), ABGMSoundActor::StaticClass()));
	GetGameInstance()->GetSubsystem<USoundManagerInstance>()->SFXSound = Cast<UAudioComponent>(UGameplayStatics::GetActorOfClass(GetWorld(), ABGMSoundActor::StaticClass()));
	if (GetGameInstance()->GetSubsystem<USoundManagerInstance>()->BGMSound != nullptr)
	{
		GetGameInstance()->GetSubsystem<USoundManagerInstance>()->BGMSound->Play();
		UE_LOG(LogTemp, Log, TEXT("BGM Played"));
	}
	else 
	{
		UE_LOG(LogTemp, Log, TEXT("BGM is null"));
	}
}
