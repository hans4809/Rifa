// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplyEntryWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DialogReplyObject.h"
#include "DialogWidget.h"

UReplyEntryWidget::UReplyEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UReplyEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReplyButton = Cast<UButton>(GetWidgetFromName(TEXT("ReplyButton")));
	ReplyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ReplyText")));
	ReplyButton->OnClicked.AddDynamic(this, &UReplyEntryWidget::ReplyButtonClicked);
	ReplyButton->OnHovered.AddDynamic(this, &UReplyEntryWidget::ReplyButtonHovered);
	ReplyButton->OnUnhovered.AddDynamic(this, &UReplyEntryWidget::ReplyButtonUnHovered);

	switch (ReplyIndex)
	{
	case 0:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImage0);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImage0);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImage0);
		break;
	case 1:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImage1);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImage1);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImage1);
		break;
	case 2:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImage0);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImage0);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImage0);
		break;
	case 3:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImage1);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImage1);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImage1);
		break;
	default:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImage0);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImage0);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImage0);
		break;
	}

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

void UReplyEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	DialogReplyObject_C = Cast<UDialogReplyObject>(ListItemObject);
	ReplyText->SetText(DialogReplyObject_C->Reply);
}

void UReplyEntryWidget::SetReplyIndex(uint32 index)
{
	ReplyIndex = index;
}
