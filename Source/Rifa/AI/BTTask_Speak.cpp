// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Speak.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/NPCAIController.h"
#include "Widget/DialogWidget.h"
#include "Widget/DialogComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_Speak::UBTTask_Speak()
{
	DialogWidget.SelectedKeyName = TEXT("DialogWidget");
	DialogWidget.SelectedKeyType = UDialogWidget::StaticClass();
}

EBTNodeResult::Type UBTTask_Speak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerCompRef = &OwnerComp;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UDialogWidget* DialogWidgetAsset = Cast<UDialogWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(DialogWidget.SelectedKeyName));
	if (DialogWidgetAsset == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	DialogWidgetAsset->OnSpeakFinished.AddDynamic(this, &UBTTask_Speak::OnSpeakFinished_Evt);
	DialogWidgetAsset->Speak_C(SpeakText);

	Result = EBTNodeResult::InProgress;
	return Result;
}

void UBTTask_Speak::OnSpeakFinished_Evt()
{
	FinishLatentTask(*OwnerCompRef, EBTNodeResult::Succeeded);
}