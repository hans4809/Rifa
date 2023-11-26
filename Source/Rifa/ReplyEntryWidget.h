// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReplyEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UReplyEntryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReplyButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ReplyText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FLinearColor HoveredColor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FLinearColor DefaultColor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UDialogReplyObject* DialogReplyObject_C;
public:
	UFUNCTION(BlueprintCallable)
	void NativeConstruct();
	UFUNCTION(BlueprintCallable)
	void ReplyButtonClicked();
	UFUNCTION(BlueprintCallable)
	void ReplyButtonHovered();
	UFUNCTION(BlueprintCallable)
	void ReplyButtonUnHovered();
};
