// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "DialogReplyObject.h"

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReplySizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("ReplySizeBox")));
	SpeakSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("SpeakSizeBox")));
	SpeakText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SpeakText")));
	ReplyList = Cast<UListView>(GetWidgetFromName(TEXT("ReplyList")));
	SetKeyboardFocus();
}

void UDialogWidget::Init()
{
	Super::Init();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
}

void UDialogWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UDialogWidget::Speak_C(FText Text)
{
	SpeakText->SetText(Text);
	SetDialogState_C(EDialogState_C::Speak);
}

void UDialogWidget::Reply_C(TArray<FText> Replies)
{
	ReplyList->ClearListItems();
	for (int i = 0; i < Replies.Num(); i++)
	{
		UDialogReplyObject* ReplyObj = NewObject<UDialogReplyObject>(this);
		ReplyObj->Reply = Replies[i];
		ReplyList->AddItem(ReplyObj);
		ReplyObj->OnClicked.AddDynamic(this, &UDialogWidget::OnClicked_Event);
		SetDialogState_C(EDialogState_C::Reply);
	}
}

void UDialogWidget::Exit_C()
{
	if (OnExit.IsBound()) { OnExit.Broadcast(); }
}

void UDialogWidget::OnClicked_Event(UDialogReplyObject* ClickedObject)
{
	if (OnReplyFinished.IsBound()) { 
		OnReplyFinished.Broadcast(ReplyList->GetIndexForItem(ClickedObject)); 
	}
}

void UDialogWidget::SetDialogState_C(EDialogState_C DialogState)
{
	CurrentDialogState = DialogState;
	switch (CurrentDialogState)
	{
	case EDialogState_C::Speak:
		ReplySizeBox->SetVisibility(ESlateVisibility::Collapsed);
		SpeakSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case EDialogState_C::Reply:
		ReplySizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SpeakSizeBox->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default:
		break;
	}
}

