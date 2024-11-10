// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FadeWidget.h"
#include "Character/RifaCharacter.h"
#include "Animation/WidgetAnimation.h"
#include <Kismet/GameplayStatics.h>

void UFadeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	EndDelegate.BindDynamic(this, &UFadeWidget::AnimationFinished);
	BindToAnimationFinished(FadeIn, EndDelegate);
}

void UFadeWidget::AnimationFinished()
{
	auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (IsValid(Player))
	{
		Player->EnableInput(Cast<APlayerController>(Player->Controller));
	}
	CloseWidget();
}
