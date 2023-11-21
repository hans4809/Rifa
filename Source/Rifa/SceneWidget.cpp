// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneWidget.h"

void USceneWidget::Init()
{
	Super::Init();
	AddToViewport(0);
}

void USceneWidget::CloseWidget()
{
	RemoveFromParent();
}

