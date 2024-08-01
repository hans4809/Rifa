// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CreditWidget.h"
#include "Character/RifaCharacter.h"
#include "Animation/WidgetAnimation.h"
#include <Kismet/GameplayStatics.h>

void UCreditWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EndDelegate.BindDynamic(this, &UCreditWidget::AnimationFinished);
	BindToAnimationFinished(Credit, EndDelegate);
	PlayAnimation(Credit);
	ARifaCharacter* Player = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->DisableInput(Cast<APlayerController>(Player->Controller));
	}
}

void UCreditWidget::Init()
{
	Super::Init();
}

void UCreditWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UCreditWidget::AnimationFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	RifaGameInstance->ResetSaveData();
	ARifaCharacter* Player = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->EnableInput(Cast<APlayerController>(Player->Controller));
	}
}
