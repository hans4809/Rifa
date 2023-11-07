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
		Slot_0 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_0")));
		Slot_1 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_1")));
		Slot_2 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_2")));
		Slot_2 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_3")));
		Slot_4 = Cast<UInventorySlot>(GetWidgetFromName(TEXT("Slot_4")));
	}
}

void UGameHUD::RefreshInventory_C()
{
	SetActivateInventory(true);
	TArray<UInventorySlot*> SlotArray;
	SlotArray.Init(nullptr, 5);
	SlotArray[0] = Slot_0;
	SlotArray[1] = Slot_1;
	SlotArray[2] = Slot_2;
	SlotArray[3] = Slot_3;
	SlotArray[4] = Slot_4;
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



