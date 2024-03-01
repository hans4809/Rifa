// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "InventorySlot.h"
#include "ActionMenuWidget.h"
#include "Components/Button.h"

void UCollectionWidget::NativeConstruct()
{
	DoOnce.Reset();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(SlotClass))
	{
		for (int i = 0; i < 15; i++)
		{
			FString SlotName = FString::Printf(TEXT("Slot_%d"), i);
			SlotArray.Add(Cast<UInventorySlot>(GetWidgetFromName(FName(SlotName))));
			SlotArray[i]->IsHave = RifaGameInstance->SoundItemHavingMap[(EItem)i];
		}
	}
	if (IsValid(ActionMenuClass))
	{
		for (int i = 0; i < 15; i++)
		{
			FString ActionMenuName = FString::Printf(TEXT("ActionMenu_%d"), i);
			ActionMenuArray.Add(Cast<UActionMenuWidget>(GetWidgetFromName(FName(ActionMenuName))));
			//SlotArray[i]->IsHave = RifaGameInstance->SoundItemMap[(Item)i];
			ActionMenuArray[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UCollectionWidget::Init()
{
	Super::Init();
	RefreshInventory_C();
}

void UCollectionWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UCollectionWidget::RefreshInventory_C()
{
	for (int i = 0; i < SlotArray.Num(); i++)
	{
		SlotArray[i]->IsHave = RifaGameInstance->SoundItemHavingMap[(EItem)i];
		//SlotArray[i]->IsHave = true;
		if (SlotArray[i]->IsHave)
		{
			SlotArray[i]->HavingImage = HavingImage;
			if (DoOnce.Execute())
			{
				for (int j = 0; j < SlotArray.Num(); j++)
				{
					if (!SlotArray[j]->ButtonWasClicked.IsBound()) 
					{
						SlotArray[j]->ButtonWasClicked.AddDynamic(this, &UCollectionWidget::ButtonWasClicked_Evt);
					}
				}
			}
		}
	}
}

void UCollectionWidget::ButtonWasClicked_Evt(int SlotClicked)
{
	if (!RifaGameInstance->SoundItemHavingMap[(EItem)SlotClicked])
	{
		return;
	}
	else 
	{
		InventorySlotClicked = SlotClicked;
		ActionMenuArray[InventorySlotClicked]->SetVisibility(ESlateVisibility::Visible);
	}

}
