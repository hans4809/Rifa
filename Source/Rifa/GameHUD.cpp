// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySlot.h"

void UGameHUD::NativeConstruct()
{
	DoOnce.Reset();
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
		for (int i = 0; i < 16; i++) 
		{
			switch (i) 
			{
				case 0:
					Slot_0 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_0")));
					SlotArray.Add(Slot_0);
				case 1:
					Slot_1 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_1")));
					SlotArray.Add(Slot_1);
				case 2:
					Slot_2 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_2")));
					SlotArray.Add(Slot_2);
				case 3:
					Slot_3 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_3")));
					SlotArray.Add(Slot_3);
				case 4:
					Slot_4 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_4")));
					SlotArray.Add(Slot_4);
				case 5:
					Slot_5 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_5")));
					SlotArray.Add(Slot_5);
				case 6:
					Slot_6 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_6")));
					SlotArray.Add(Slot_6);
				case 7:
					Slot_7 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_7")));
					SlotArray.Add(Slot_7);
				case 8:
					Slot_8 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_8")));
					SlotArray.Add(Slot_8);
				case 9:
					Slot_9 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_9")));
					SlotArray.Add(Slot_9);
				case 10:
					Slot_10 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_10")));
					SlotArray.Add(Slot_10);
				case 11:
					Slot_11 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_11")));
					SlotArray.Add(Slot_11);
				case 12:
					Slot_12 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_12")));
					SlotArray.Add(Slot_12);
				case 13:
					Slot_13 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_13")));
					SlotArray.Add(Slot_13);
				case 14:
					Slot_14 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_14")));
					SlotArray.Add(Slot_14);
				case 15:
					Slot_15 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_15")));
					SlotArray.Add(Slot_15);
			}
		}
	}
}

void UGameHUD::RefreshInventory_C()
{
	SetActivateInventory(true);
	for(int i = 0; i < SlotArray.Num(); i++)
	{ 
		if (i < Inventory.Num())
		{
			SlotArray[i]->PickupImage = Inventory[i].ItemImage;
			if (DoOnce.Execute()) 
			{
				for(int j = 0; j < SlotArray.Num(); j++)
				{
					if (SlotArray[j]->ButtonWasClicked.IsBound()) {
						SlotArray[j]->ButtonWasClicked.Clear();
					}

					SlotArray[j]->ButtonWasClicked.AddDynamic(this, &UGameHUD::ButtonWasClicked_Evt);
				}
			}
		}
		else 
		{
			SlotArray[i]->PickupImage = nullptr;
		}
	}
}

void UGameHUD::ButtonWasClicked_Evt(int SlotClicked)
{
	ActivateInventory = false;
	InventorySlotClicked = SlotClicked;
	ActionText = Inventory[SlotClicked].AcitonText;
	ActionMenuVisible = ESlateVisibility::Visible;
}

//UUMGSequencePlayer* UGameHUD::PlayAnimation(UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, EUMGSequencePlayMode::Type PlayMode, float PlaybackSpeed, bool bRestoreState)
//{
	//Super::PlayAnimation(InAnimation, StartAtTime, NumLoopsToPlay, PlayMode, PlaybackSpeed, bRestoreState);
//}




