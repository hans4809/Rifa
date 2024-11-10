// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySlot.h"
#include "Data/MyGameInstance.h"
#include "Components/SizeBox.h"
#include "GameSettingWidget.h"

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void UGameHUD::Init()
{
	Super::Init();
}




