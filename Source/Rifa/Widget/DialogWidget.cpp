// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "DialogReplyObject.h"
#include "Components/ListView.h"
#include "ReplyEntryWidget.h"

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReplySizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("ReplySizeBox")));
	SpeakSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("SpeakSizeBox")));
	SpeakText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SpeakText")));
	ReplyList = Cast<UListView>(GetWidgetFromName(TEXT("ReplyList")));
 }

void UDialogWidget::Init()
{
	Super::Init();
}

void UDialogWidget::CloseWidget()
{
	Super::CloseWidget();
	SpeakText->SetText(FText::FromString(TEXT("")));
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
		ReplyObj->ReplyIndex = i;
		ReplyList->AddItem(ReplyObj);
		ReplyObj->OnClicked.AddDynamic(this, &UDialogWidget::OnClicked_Event);
		SetDialogState_C(EDialogState_C::Reply);
	}

	//AdjustListViewSize(ReplyList, ReplySizeBox, 50.0f, 275.0f);
}


void UDialogWidget::Exit_C()
{
	if (OnExit.IsBound()) { OnExit.Broadcast(); }
}

void UDialogWidget::OnClicked_Event(UDialogReplyObject* ClickedObject)
{
	if (OnReplyFinished.IsBound())
	{ 
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
		SpeakSizeBox->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}
}

void UDialogWidget::AdjustListViewSize(UListView* ListView, USizeBox* ContainerSizeBox, float ItemHeight, float MaxHeight)
{
	if (!ListView || !ContainerSizeBox)
	{
		return;  // ListView 또는 ContainerSizeBox가 nullptr인 경우 함수를 종료합니다.
	}

	// 아이템의 총 개수 가져오기
	int32 ItemCount = ListView->GetNumItems();

	// 전체 높이를 아이템 수와 아이템 높이를 곱하여 계산
	float CalculatedHeight = ItemCount * ItemHeight;

	// 최대 높이를 초과하지 않도록 설정
	float FinalHeight = FMath::Min(CalculatedHeight, MaxHeight);

	// SizeBox의 높이를 설정하여 ListView의 크기를 조정
	ContainerSizeBox->SetHeightOverride(FinalHeight);
}

FReply UDialogWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply returnReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (CurrentDialogState != EDialogState_C::Speak)
	{
		return returnReply;
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (OnSpeakFinished.IsBound()) { OnSpeakFinished.Broadcast(); }
	}

	returnReply = FReply::Handled();

	return returnReply;
}

FReply UDialogWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply returnReply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (CurrentDialogState != EDialogState_C::Speak)
	{
		return returnReply;
	}

	if (InKeyEvent.GetKey() == EKeys::SpaceBar)
	{
		if (OnSpeakFinished.IsBound()) { OnSpeakFinished.Broadcast(); }
	}

	returnReply = FReply::Handled();

	return returnReply;
}

