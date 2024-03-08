// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "GameSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UGameSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void ReturnButtonClicked();
	UFUNCTION(BlueprintCallable)
	void SoundButtonClicked();
	UFUNCTION(BlueprintCallable)
	void GraphicButtonClicked();
	UFUNCTION(BlueprintCallable)
	void InputButtonClicked();
	UFUNCTION(BlueprintCallable)
	void MainButtonClicked();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> SoundSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundSettingWidget> SoundSettingWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> GraphicSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGraphicSettingWidget> GraphicSettingWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> InputSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputSettingWidget> InputSettingWidgetAsset;
private:

protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> SoundButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> GraphicButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> ControlButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> ReturnButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> SaveButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<class UButton> MainButton;
};
