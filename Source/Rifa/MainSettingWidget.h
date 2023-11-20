// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopUpWidget.h"
#include "MainSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UMainSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
private:
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SoundButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* GraphicButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ControlButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void SoundButtonClicked();
	UFUNCTION(BlueprintCallable)
	void GraphicButtonClicked();
	UFUNCTION(BlueprintCallable)
	void InputButtonClicked();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> SoundSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class USoundSettingWidget* SoundSettingWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> GraphicSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UGraphicSettingWidget* GraphicSettingWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> InputSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UInputSettingWidget* InputSettingWidgetAsset;
};
