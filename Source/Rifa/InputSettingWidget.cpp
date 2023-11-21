// Fill out your copyright notice in the Description page of Project Settings.


#include "InputSettingWidget.h"
#include "Components/Button.h"
#include "RifaCharacter.h"
#include "Components/InputKeySelector.h"
#include "Framework/Commands/InputChord.h"
#include "Widgets/Input/SInputKeySelector.h"
#include "Styling/UMGCoreStyle.h"
#include "InputMappingContext.h"
#include "EnhancedActionKeyMapping.h"


void UInputSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	ReturnButton->OnClicked.AddDynamic(this, &UInputSettingWidget::CloseWidget);
	InteractionKeySelector = Cast<UInputKeySelector>(GetWidgetFromName(TEXT("InteractionKeySelector")));
	SwimKeySelector = Cast<UInputKeySelector>(GetWidgetFromName(TEXT("SwimKeySelector")));
	FlyKeySelector = Cast<UInputKeySelector>(GetWidgetFromName(TEXT("FlyKeySelector")));
	JumpKeySelector = Cast<UInputKeySelector>(GetWidgetFromName(TEXT("JumpKeySelector")));
	MoveKeySelector = Cast<UInputKeySelector>(GetWidgetFromName(TEXT("MoveKeySelector")));
	DefaultInputMappings = DefaultMappingContext->GetMappings();
	for (int i = 0; i < DefaultInputMappings.Num(); i++)
	{
		if (DefaultInputMappings[i].Action == JumpAction) 
		{
			JumpKeySelector->SetSelectedKey(FInputChord(DefaultInputMappings[i].Key));
			CurrentJumpKey = DefaultInputMappings[i].Key;
		}
		else if (DefaultInputMappings[i].Action == FlyAction)
		{
			FlyKeySelector->SetSelectedKey(FInputChord(DefaultInputMappings[i].Key));
			CurrentFlyKey = DefaultInputMappings[i].Key;
		}
		else if (DefaultInputMappings[i].Action == SwimAction)
		{
			SwimKeySelector->SetSelectedKey(FInputChord(DefaultInputMappings[i].Key));
			CurrentSwimKey = DefaultInputMappings[i].Key;
		}
	}
	SwimKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &UInputSettingWidget::SwimKeyChangedClicked);
	SwimKeySelector->OnKeySelected.AddDynamic(this, &UInputSettingWidget::SwimKeyChanged);
}

void UInputSettingWidget::Init()
{
	Super::Init();
}

void UInputSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UInputSettingWidget::SwimKeyChangedClicked()
{
	ListenforRemap = true;
}

void UInputSettingWidget::SwimKeyChanged(const FInputChord SelectedKey)
{
	KeyChanged(SelectedKey, SwimAction, CurrentSwimKey);
}

void UInputSettingWidget::KeyChanged(const FInputChord SelectedKey, UInputAction* Action, FKey CurrentKey)
{
	if (ListenforRemap) {
		ListenforRemap = false;
		DefaultMappingContext->UnmapKey(Action, CurrentKey);
		DefaultMappingContext->MapKey(Action, SelectedKey.Key);
		CurrentKey = SelectedKey.Key;
	}
}


