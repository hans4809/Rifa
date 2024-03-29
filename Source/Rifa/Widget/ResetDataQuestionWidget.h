// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/PopUpWidget.h"
#include "ResetDataQuestionWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UResetDataQuestionWidget : public UPopUpWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void OnYesButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnNoButtonClicked();
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> YesButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> NoButton;	
	void NativeConstruct() override;
};
