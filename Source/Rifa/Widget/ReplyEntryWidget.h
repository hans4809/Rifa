// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ReplyEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UReplyEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UReplyEntryWidget(const FObjectInitializer& ObjectInitializer);
	
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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true))
	class UTexture2D* ReplyImage0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true))
	class UTexture2D* ReplyImage1;
public:
	UFUNCTION(BlueprintCallable)
	void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void ReplyButtonClicked();
	UFUNCTION(BlueprintCallable)
	void ReplyButtonHovered();
	UFUNCTION(BlueprintCallable)
	void ReplyButtonUnHovered();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void SetReplyIndex(uint32 index);
private:
	uint32 ReplyIndex;
};
