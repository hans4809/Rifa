// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SceneWidget.h"
#include "RifaMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API URifaMainHUD : public USceneWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResetButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* LoadButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SettingButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;
public:
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> MainSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UMainSettingWidget* MainSettingWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundCue* MainBGM;
	UFUNCTION(BlueprintCallable)
	void SettingButtonClicked();
};
