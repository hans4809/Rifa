// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EndingKeyWidget.h"
#include "Character/RifaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequencePlayer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/CreditWidget.h"

UEndingKeyWidget::UEndingKeyWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CreditWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_Credit.WG_Credit_C'"));
	if (CreditWidgetClassFinder.Succeeded())
	{
		CreditWidgetClass = CreditWidgetClassFinder.Class;
	}
}

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
	if (CreditWidgetClass)
	{
		CreditWidgetAsset = CreateWidget<UCreditWidget>(GetWorld(), CreditWidgetClass);
	}
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
	//UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	if (CreditWidgetAsset)
	{
		CreditWidgetAsset->Init();
	}
}
