// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "DoOnce.h"
#include "CollectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UCollectionWidget : public UPopUpWidget
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void RefreshInventory_C();
	UFUNCTION(BlueprintCallable)
	void ButtonWasClicked_Evt(int SlotClicked);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetActivateInventory() { return bActivateInventory; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActivateInventory(bool _bActivateInventory) { bActivateInventory = _bActivateInventory; }
	/*UFUNCTION(BlueprintCallable)
	FORCEINLINE ESlateVisibility GetActionMenuVisible() { return ActionMenuVisible; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActionMenuVisible(ESlateVisibility _ActionMenuVisible) { ActionMenuVisible = _ActionMenuVisible; }*/
protected:
	void NativeConstruct() override;
	UPROPERTY(VisibleAnywhere)
	FDoOnce DoOnce;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
	/*UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	ESlateVisibility ActionMenuVisible = ESlateVisibility::Hidden;*/
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	FString ActionText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	int InventorySlotClicked;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	bool bActivateInventory = true;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ReturnButton;
//Slot Reference
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SlotClass;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_0;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_1;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_2;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_3;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_4;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_5;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_6;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_7;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_8;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_9;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_10;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_11;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_12;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_13;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UInventorySlot> Slot_14;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Collection", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<class UInventorySlot>> SlotArray;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Collection", meta = (AllowPrivateAccess = true))
	UTexture2D* HavingImage;
//ActionMenu Reference
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ActionMenuClass;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_0;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_1;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_2;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_3;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_4;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_5;	
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_6;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_7;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_8;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_9;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_10;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_11;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_12;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_13;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<class UActionMenuWidget> ActionMenu_14;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ActionMenu", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<class UActionMenuWidget>> ActionMenuArray;

};
