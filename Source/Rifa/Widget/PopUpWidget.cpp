// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpWidget.h"
#include "Data/MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "SceneWidget.h"
#include "GameHUD.h"

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
	if (IsValid(Cast<UPopUpWidget>(ParentWidget)))
	{
		ParentWidget->SetKeyboardFocus();
	}
	else if(IsValid(Cast<UGameHUD>(ParentWidget)))
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	}

	RemoveFromParent();
}

FReply UPopUpWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply returnReply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (InKeyEvent.GetKey() == EKeys::Escape)
		CloseWidget();
	
	returnReply = FReply::Handled();

	return returnReply;
}

void UPopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetKeyboardFocus();
}
