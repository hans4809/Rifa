// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStruct.h"
#include "SceneWidget.h"
#include "DoOnce.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UGameHUD : public USceneWidget
{
	GENERATED_BODY()
public:
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = true))
	class ARifaCharacter* CharacterReference;
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = true))
	class UMyGameInstance* RifaGameInstance;
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	//Inventory 정보를 나중에 CharacterController에 옮기는게 좋을 수 있다.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ARifaCharacter* GetCharacterReference() { return CharacterReference; }
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UPanelWidget> SizeBoxClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class USizeBox* FlyEnergySizeBox;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class USizeBox* SwimEnergySizeBox;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> GameSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGameSettingWidget> GameSettingWidgetAsset;
	//UFUNCTION(BlueprintCallable)
	//virtual UUMGSequencePlayer* PlayAnimation(UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f, bool bRestoreState = false);
};
