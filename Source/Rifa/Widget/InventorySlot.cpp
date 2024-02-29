// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"

void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton")));
	if (ItemButton->OnClicked.IsBound()) {
		ItemButton->OnClicked.Clear();
	}

	ItemButton->OnClicked.AddDynamic(this, &UInventorySlot::ButtonWasClicked_Event);
}
void UInventorySlot::NativeDestruct()
{
	Super::NativeDestruct();
	ButtonWasClicked.Clear();
}
void UInventorySlot::ButtonWasClicked_Event()
{
	if (ButtonWasClicked.IsBound() == true){ ButtonWasClicked.Broadcast(InventorySlot); }
}


