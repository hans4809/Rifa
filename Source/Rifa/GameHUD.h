// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStruct.h"
#include "DoOnce.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> RifaCharacterClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = true))
	class ARifaCharacter* CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	bool ActivateInventory = true;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	ESlateVisibility InventoryVisible = ESlateVisibility::Hidden;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	ESlateVisibility ActionMenuVisible = ESlateVisibility::Hidden;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	FString ActionText;
	//Inventory 정보를 나중에 CharacterController에 옮기는게 좋을 수 있다.
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FItemStruct> Inventory;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	int InventorySlotClicked;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SlotClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventorySlot* Slot_0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventorySlot* Slot_1;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventorySlot* Slot_2;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventorySlot* Slot_3;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventorySlot* Slot_4;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TArray<UInventorySlot*> SlotArray;
	UPROPERTY(VisibleAnywhere)
	FDoOnce DoOnce;
	UPROPERTY(VisibleAnywhere)
	int i = 0;
	UPROPERTY()
	int j = 0;
public:
	UFUNCTION(BlueprintCallable)
	void RefreshInventory_C();
	UFUNCTION(BlueprintCallable)
	void ButtonWasClicked_Evt(int SlotClicked);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ARifaCharacter* GetCharacterReference() { return CharacterReference; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetActivateInventory() { return ActivateInventory; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActivateInventory(bool _ActivateInventory) { ActivateInventory = _ActivateInventory; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ESlateVisibility GetInventoryVisible() { return InventoryVisible; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetInventoryVisible(ESlateVisibility _InventoryVisible) { InventoryVisible = _InventoryVisible; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ESlateVisibility GetActionMenuVisible() { return ActionMenuVisible; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActionMenuVisible(ESlateVisibility _ActionMenuVisible) { ActionMenuVisible = _ActionMenuVisible; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<FItemStruct> GetInventory() { return Inventory; }
};
