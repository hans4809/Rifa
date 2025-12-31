// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequence/EndingLevelSequencePlayActor.h"
#include "Widget/EndingKeyWidget.h"
#include "Components/BoxComponent.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RifaCharacter.h"
#include "Animation/SkeletalMeshActor.h"
#include "Data/MyGameInstance.h"
#include "Widget/GameHUD.h"
#include "LevelScript/FieldLevelScriptActor.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"

AEndingLevelSequencePlayActor::AEndingLevelSequencePlayActor()
{

}

void AEndingLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(this)) {
		return;
	}

	if (IsValid(EndingKeyWidgetClass))
		EndingKeyWidgetAsset = CreateWidget<UEndingKeyWidget>(GetWorld(), EndingKeyWidgetClass);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEndingLevelSequencePlayActor::OnCharacterOverlap);

	LevelSequencePlayer->OnFinished.AddDynamic(this, &AEndingLevelSequencePlayActor::EndLevelSequence);
}

void AEndingLevelSequencePlayActor::PlayLevelSequence()
{
	Super::PlayLevelSequence();
	auto levelScriptActor = Cast<AFieldLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (levelScriptActor)
	{
		auto gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstance)
		{
			gameInstance->BGMIndex = 4;
		}
		levelScriptActor->BGMActor->GetAudioComponent()->SetIntParameter(FName(TEXT("BGMIndex")), 4);
	}
}

void AEndingLevelSequencePlayActor::EndLevelSequence()
{
	Super::EndLevelSequence();

	if (EndingKeyWidgetAsset) 
		EndingKeyWidgetAsset->Init();
}

void AEndingLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(Cast<ARifaCharacter>(OtherActor))
		PlayLevelSequence();
}
