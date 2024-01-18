// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelScriptActor.h"
#include <Kismet/GameplayStatics.h>
#include "LevelSequenceCharacterActor.h"

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceCharacterActor::StaticClass(), LevelSequenceCharacterArr);
}
