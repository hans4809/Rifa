// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/Image.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TutorialImage = Cast<UImage>(GetWidgetFromName(TEXT("TutorialImage")));
}
