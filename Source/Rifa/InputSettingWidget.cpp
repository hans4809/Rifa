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
			JumpKeySelector->SetSelectedKey(DefaultInputMappings[i].Key);
		}
		else if (DefaultInputMappings[i].Action == FlyAction)
		{
			FlyKeySelector->SetSelectedKey(DefaultInputMappings[i].Key);
		}
		else if (DefaultInputMappings[i].Action == SwimAction)
		{
			SwimKeySelector->SetSelectedKey(DefaultInputMappings[i].Key);
		}
	}
}

void UInputSettingWidget::Init()
{
	Super::Init();
}

void UInputSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}