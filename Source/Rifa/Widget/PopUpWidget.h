// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PopUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UPopUpWidget : public UBaseWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void CloseWidget() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UBaseWidget> ParentWidget;
protected:
	void NativeConstruct() override;
};