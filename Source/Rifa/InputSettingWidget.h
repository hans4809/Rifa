// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "InputMappingContext.h"
#include "EnhancedActionKeyMapping.h"
#include "InputSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UInputSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InterAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FKey CurrentInterActionKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FKey CurrentJumpKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FKey CurrentMoveKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlyAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FKey CurrentFlyKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwimAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FKey CurrentSwimKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<FEnhancedActionKeyMapping> DefaultInputMappings;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInputKeySelector* InteractionKeySelector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInputKeySelector* SwimKeySelector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInputKeySelector* FlyKeySelector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInputKeySelector* MoveKeySelector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInputKeySelector* JumpKeySelector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool ListenforRemap;
public:
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void KeyChangedClicked();
	UFUNCTION(BlueprintCallable)
	void SwimKeyChanged(const FInputChord SelectedKey);
	UFUNCTION(BlueprintCallable)
	void InterActionKeyChanged(const FInputChord SelectedKey);
	UFUNCTION(BlueprintCallable)
	void FlyKeyChanged(const FInputChord SelectedKey);
	UFUNCTION(BlueprintCallable)
	void JumpKeyChanged(const FInputChord SelectedKey);
	UFUNCTION(BlueprintCallable)
	void KeyChanged(const FInputChord SelectedKey, class UInputAction* Action, FKey CurrentKey);
};
