// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EndingKeyWidget.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequencePlayer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include <Character/RifaPlayerController.h>

UEndingKeyWidget::UEndingKeyWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/*static ConstructorHelpers::FObjectFinder<ULevelSequence> levelSequence(TEXT("/Script/LevelSequence.LevelSequence'/Game/LevelSequence/LevelSequence10'"));
	if (levelSequence.Succeeded())
	{
		EndingLevelSequence = levelSequence.Object;
	}*/
}

void UEndingKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto characterController = Cast<ARifaPlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController());

	if (IsValid(EndingLevelSequence)) 
	{
		EndingLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndingLevelSequence, FMovieSceneSequencePlaybackSettings(), EndingLevelSequenceActor);
		if (IsValid(EndingLevelSequencePlayer))
		{
			EndingLevelSequencePlayer->OnPlay.AddDynamic(characterController, &ARifaPlayerController::OnStartedLevelSequence);
			EndingLevelSequencePlayer->OnFinished.AddDynamic(characterController, &ARifaPlayerController::OnFinishedGame);
			//EndingLevelSequencePlayer->OnFinished.AddDynamic(characterController, &ARifaPlayerController::OnFinishedLevelSequence);
		}

	}

	characterController->SetInputMode(FInputModeUIOnly());
}

FReply UEndingKeyWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply returnReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		PlayEndingLevelSequence();
	}

	returnReply = FReply::Handled();

	return returnReply;
}

void UEndingKeyWidget::PlayEndingLevelSequence()
{
	if (!RifaGameInstance->LevelSequencePlayerArr[10])
	{
		if (IsValid(EndingLevelSequencePlayer))
		{
			//UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
			FMovieSceneSequencePlaybackParams Param;
			EndingLevelSequencePlayer->SetPlaybackPosition(Param);
			EndingLevelSequencePlayer->Play();
			RifaGameInstance->LevelSequencePlayerArr[10] = true;
			this->CloseWidget();
		}
	}
}
