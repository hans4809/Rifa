// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Reply.h"
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

UBTTask_Reply::UBTTask_Reply()
{
    DialogWidget.SelectedKeyName = TEXT("DialogWidget");
    DialogWidget.SelectedKeyType = UDialogWidget::StaticClass();
    OutReplyIndex.SelectedKeyName = TEXT("ReplyIndex");
}

EBTNodeResult::Type UBTTask_Reply::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    OwnerCompRef = &OwnerComp;
    AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if(ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

    UDialogWidget* DialogWidgetAsset = Cast<UDialogWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(DialogWidget.SelectedKeyName));
    if(DialogWidgetAsset == nullptr)
	{
		return EBTNodeResult::Failed;
	}

    DialogWidgetAsset->OnReplyFinished.AddDynamic(this, &UBTTask_Reply::OnReplyFinished_Evt);

    DialogWidgetAsset->Reply_C(Replies);
    Result = EBTNodeResult::InProgress;
    return Result;
}

void UBTTask_Reply::OnReplyFinished_Evt(int32 Index)
{
    AIController->GetBlackboardComponent()->SetValueAsInt(OutReplyIndex.SelectedKeyName, Index);
    FinishLatentTask(*OwnerCompRef, EBTNodeResult::Succeeded);
}
