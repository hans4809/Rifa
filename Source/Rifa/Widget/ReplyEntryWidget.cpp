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

	if(ReplyButton->OnClicked.IsBound())
		ReplyButton->OnClicked.Clear();
	if (ReplyButton->OnHovered.IsBound())
		ReplyButton->OnHovered.Clear();
	if (ReplyButton->OnUnhovered.IsBound())
		ReplyButton->OnUnhovered.Clear();

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

void UReplyEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	DialogReplyObject_C = Cast<UDialogReplyObject>(ListItemObject);
	ReplyText->SetText(DialogReplyObject_C->Reply);

	switch (DialogReplyObject_C->ReplyIndex)
	{
	case 0:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImageA);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImageA);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImageA);
		break;
	case 1:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImageB);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImageB);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImageB);
		break;
	case 2:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImageC);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImageC);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImageC);
		break;
	default:
		ReplyButton->WidgetStyle.Normal.SetResourceObject(ReplyImageA);
		ReplyButton->WidgetStyle.Hovered.SetResourceObject(ReplyImageA);
		ReplyButton->WidgetStyle.Pressed.SetResourceObject(ReplyImageA);
		break;
	}
}
