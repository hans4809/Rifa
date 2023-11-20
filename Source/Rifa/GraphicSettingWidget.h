// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "InputMappingContext.h"
#include "GraphicSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UGraphicSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
public:
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget() override;
};
