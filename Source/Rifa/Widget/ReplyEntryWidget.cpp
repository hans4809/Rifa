// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplyEntryWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DialogReplyObject.h"
#include "DialogWidget.h"

void UReplyEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReplyButton = Cast<UButton>(GetWidgetFromName(TEXT("ReplyButton")));
	ReplyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ReplyText")));
	ReplyButton->OnClicked.AddDynamic(this, &UReplyEntryWidget::ReplyButtonClicked);
	ReplyButton->OnHovered.AddDynamic(this, &UReplyEntryWidget::ReplyButtonHovered);
	ReplyButton->OnUnhovered.AddDynamic(this, &UReplyEntryWidget::ReplyButtonUnHovered);

	UDialogWidget* Parent = Cast<UDialogWidget>(GetParent());
	if (IsValid(Parent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent %s is valid"), *Parent->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent is invalid"));
	}
}

void UReplyEntryWidget::ReplyButtonClicked()
{
	if (IsValid(DialogReplyObject_C))
	{
		if (DialogReplyObject_C->OnClicked.IsBound()) { DialogReplyObject_C->OnClicked.Broadcast(DialogReplyObject_C); }
	}
}

void UReplyEntryWidget::ReplyButtonHovered()
{
	ReplyText->SetColorAndOpacity(HoveredColor);
}

void UReplyEntryWidget::ReplyButtonUnHovered()
{
	ReplyText->SetColorAndOpacity(DefaultColor);
}
