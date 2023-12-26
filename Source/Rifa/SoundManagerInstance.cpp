// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManagerInstance.h"
#include "Sound/AmbientSound.h"
#include "Audio.h"
#include "Components/AudioComponent.h"

USoundManagerInstance::USoundManagerInstance()
{
	BGMSound = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMSound"));
	SFXSound = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXSound"));
}
