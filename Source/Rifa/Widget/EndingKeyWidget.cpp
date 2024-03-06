// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EndingKeyWidget.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequencePlayer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UEndingKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(EndingLevelSequence)) 
	{
		EndingLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndingLevelSequence, FMovieSceneSequencePlaybackSettings(), EndingLevelSequenceActor);
	}
	Cast<APlayerController>(CharacterReference->GetController())->SetInputMode(FInputModeUIOnly());
}

void UEndingKeyWidget::PlayEndingLevelSequence()
{
	if (!RifaGameInstance->LevelSequencePlayerArr[10])
	{
		if (IsValid(CharacterReference) && IsValid(EndingLevelSequencePlayer))
		{
			UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
			CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
			FTimerHandle LevelSequenceTimer;
			FMovieSceneSequencePlaybackParams Param;
			EndingLevelSequencePlayer->SetPlaybackPosition(Param);
			EndingLevelSequencePlayer->Play();
			GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &UEndingKeyWidget::EndEndingLevelSequence, EndingLevelSequencePlayer->GetDuration().AsSeconds(), false);

			RifaGameInstance->LevelSequencePlayerArr[10] = true;
		}
	}
}

void UEndingKeyWidget::EndEndingLevelSequence()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	RifaGameInstance->ResetSaveData();
}
