// Fill out your copyright notice in the Description page of Project Settings.


#include "InputSettingWidget.h"
#include "Components/Button.h"
#include "Character/RifaCharacter.h"
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
		else if (DefaultInputMappings[i].Action == InterAction)
		{
			InteractionKeySelector->SetSelectedKey(FInputChord(DefaultInputMappings[i].Key));
			CurrentInterActionKey = DefaultInputMappings[i].Key;
		}
	}
	SwimKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &UInputSettingWidget::KeyChangedClicked);
	SwimKeySelector->OnKeySelected.AddDynamic(this, &UInputSettingWidget::SwimKeyChanged);
	InteractionKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &UInputSettingWidget::KeyChangedClicked);
	InteractionKeySelector->OnKeySelected.AddDynamic(this, &UInputSettingWidget::InterActionKeyChanged);
	FlyKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &UInputSettingWidget::KeyChangedClicked);
	FlyKeySelector->OnKeySelected.AddDynamic(this, &UInputSettingWidget::FlyKeyChanged);
	JumpKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &UInputSettingWidget::KeyChangedClicked);
	JumpKeySelector->OnKeySelected.AddDynamic(this, &UInputSettingWidget::JumpKeyChanged);
}

void UInputSettingWidget::Init()
{
	Super::Init();
}

void UInputSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UInputSettingWidget::KeyChangedClicked()
{
	ListenforRemap = true;
}

void UInputSettingWidget::SwimKeyChanged(const FInputChord SelectedKey)
{
	KeyChanged(SelectedKey, SwimAction, CurrentSwimKey);
}

void UInputSettingWidget::InterActionKeyChanged(const FInputChord SelectedKey)
{
	KeyChanged(SelectedKey, InterAction, CurrentInterActionKey);
}

void UInputSettingWidget::FlyKeyChanged(const FInputChord SelectedKey)
{
	KeyChanged(SelectedKey, FlyAction, CurrentFlyKey);
}

void UInputSettingWidget::JumpKeyChanged(const FInputChord SelectedKey)
{
	KeyChanged(SelectedKey, JumpAction, CurrentJumpKey);
}

void UInputSettingWidget::KeyChanged(const FInputChord SelectedKey, UInputAction* Action, FKey CurrentKey)
{
	if (ListenforRemap) {
		ListenforRemap = false;
		DefaultMappingContext->UnmapKey(Action, CurrentKey);
		for(auto Mapping : DefaultMappingContext->GetMappings())
		{
			if (Mapping.Key == SelectedKey.Key)
			{
				DefaultMappingContext->MapKey(Action, CurrentKey);
				return;
			}
		}
		DefaultMappingContext->MapKey(Action, SelectedKey.Key);
		CurrentKey = SelectedKey.Key;
	}
}


