// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySlot.h"
#include "MyGameInstance.h"
#include "Components/SizeBox.h"
#include "GameSettingWidget.h"

void UGameHUD::NativeConstruct()
{
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//캐릭터 인스턴스 참조할려고 초기화
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (CharacterReference == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Casting Failed"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Casting Successed"));
	}
}

void UGameHUD::Init()
{
	Super::Init();
}




