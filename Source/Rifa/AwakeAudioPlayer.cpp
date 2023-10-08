// Fill out your copyright notice in the Description page of Project Settings.


#include "AwakeAudioPlayer.h"

// Sets default values for this component's properties
UAwakeAudioPlayer::UAwakeAudioPlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAwakeAudioPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (soundToPlay && actorTarget)
	{
		UGameplayStatics::PlaySoundAtLocation(this, soundToPlay, actorTarget->GetActorLocation());
	}
	
}


// Called every frame
void UAwakeAudioPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UGameplayStatics::PlaySoundAtLocation(this, soundToPlay, actorTarget->GetActorLocation());
	// ...
}

