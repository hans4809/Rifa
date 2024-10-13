// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "GraphicSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UGraphicSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void NativeConstruct() override;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> FullScreenLeft;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> FullScreenRight;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ResolutionDown;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ResolutionUp;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ReturnButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ApplyButton;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> CurrentWindowMode = EWindowMode::Fullscreen;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 CurrentResolutionIndex = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FIntPoint CurrentResolutions;
protected:
	UFUNCTION(BlueprintCallable)
	void SetResolutionIndex(FIntPoint resolution);
	UFUNCTION(BlueprintCallable)
	void SetResolution(int32 resolutionIndex);
protected:
	UFUNCTION(BlueprintCallable)
	void OnFullScreenRightClicked();
	UFUNCTION(BlueprintCallable)
	void OnFullScreenLeftClicked();
	UFUNCTION(BlueprintCallable)
	void OnResolutionUpClicked();
	UFUNCTION(BlueprintCallable)
	void OnResolutionDownClicked();
	UFUNCTION(BlueprintCallable)
	void OnApplyButtonClicked();

public:
	virtual void Init() override;
	virtual void CloseWidget() override;
};
