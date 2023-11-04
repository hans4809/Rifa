// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySlot.h"

void UGameHUD::NativeConstruct()
{
	if (IsValid(RifaCharacterClass))
	{
		CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (CharacterReference == nullptr) 
		{
			UE_LOG(LogTemp, Log, TEXT("Casting Failed"));
		}
		else 
		{
			UE_LOG(LogTemp, Log, TEXT("Casting Successed"));
		}
	}
	if (IsValid(SlotClass))
	{
		Slot_0 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_0")));
		Slot_1 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_1")));
		Slot_2 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_2")));
		Slot_2 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_3")));
		Slot_4 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_4")));
	}
}

void UGameHUD::RefreshInventory_C()
{
	TArray<UInventorySlot*> tempArray;
	tempArray.Add(Slot_0);
	tempArray.Add(Slot_1);
	tempArray.Add(Slot_2);
	tempArray.Add(Slot_3);
	tempArray.Add(Slot_4);
	SetActivateInventory(true);
	/*for (int i = 0; i < tempArray.Num(); i++) 
	{
		if (GetInventory().Num() < i) 
		{
			tempArray[i]->PickupImage = Inventory[i].ItemImage;
			tempArray[i]->ButtonWasClicked.AddDynamic(this, &UGameHUD::ButtonWasClicked_Evt);
		}
		else 
		{
			tempArray[i]->PickupImage = nullptr;
		}
	}*/
}

void UGameHUD::ButtonWasClicked_Evt(int SlotClicked)
{
	ActivateInventory = false;
	InventorySlotClicked = SlotClicked;
	ActionText = Inventory[SlotClicked].AcitonText;
	ActionMenuVisible = ESlateVisibility::Visible;
}
