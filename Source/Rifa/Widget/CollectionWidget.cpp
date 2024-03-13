// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "InventorySlot.h"
#include "ActionMenuWidget.h"
#include "Components/Button.h"
#include <Character/RifaCharacter.h>
#include "LevelScript/BaseLevelScriptActor.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"

void UCollectionWidget::NativeConstruct()
{
	DoOnce.Reset();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	ReturnButton->OnClicked.AddDynamic(this, &UCollectionWidget::CloseWidget);
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
			ActionMenuArray[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (ARifaCharacter* Character = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (APlayerController* Controller = Cast<APlayerController>(Character->GetController())) 
		{
			Controller->SetInputMode(FInputModeUIOnly());
			Controller->bShowMouseCursor = true;
		}
	}
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			if (CurrentLevelScriptActor->BGMActor->GetAudioComponent()->IsPlaying())
			{
				CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(true);
			}
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
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			for (int i = 0; i < RifaGameInstance->SoundItemOnOffMap.Num(); i++)
			{
				FName Parameter = FName(FString::Printf(TEXT("Inst%d"), i));
				if (RifaGameInstance->SoundItemOnOffMap[(EItem)i] = true)
				{
					CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 1.f);
				}
				else
				{
					CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 0.f);
				}
			}
		}
	}
	
	if (RifaGameInstance->PopupSort == 4) 
	{
		if (ARifaCharacter* Character = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			if (APlayerController* Controller = Cast<APlayerController>(Character->GetController()))
			{
				Controller->SetInputMode(FInputModeGameOnly());
				Controller->bShowMouseCursor = false;
			}
		}
		if (IsValid(CurrentLevelScriptActor)) 
		{
			if (IsValid(CurrentLevelScriptActor->BGMActor))
			{
				CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);
			}
		}
	}
}

void UCollectionWidget::RefreshInventory_C()
{
	for (int i = 0; i < SlotArray.Num(); i++)
	{
		SlotArray[i]->IsHave = RifaGameInstance->SoundItemHavingMap[(EItem)i];
		if (SlotArray[i]->IsHave)
		{
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
