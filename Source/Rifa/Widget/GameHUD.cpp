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
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//캐릭터 인스턴스 참조할려고 초기화
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UGameHUD::Init()
{
	Super::Init();
}



