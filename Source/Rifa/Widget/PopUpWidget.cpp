// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpWidget.h"
#include "Data/MyGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UPopUpWidget::Init()
{
	Super::Init();
	SetInputActionPriority(Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort);
	AddToViewport(Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort++);
}

void UPopUpWidget::CloseWidget()
{
	Super::CloseWidget();
	Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort--;
	if(IsValid(Cast<UPopUpWidget>(ParentWidget)))
		ParentWidget->SetKeyboardFocus();
	RemoveFromViewport();
}

FReply UPopUpWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (InKeyEvent.GetKey() == EKeys::Escape)
		CloseWidget();
	return FReply::Handled();
}

void UPopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetKeyboardFocus();
}
