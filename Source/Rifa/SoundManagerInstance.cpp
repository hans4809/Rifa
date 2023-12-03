// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManagerInstance.h"
#include "Sound/AmbientSound.h"
#include "Audio.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

USoundManagerInstance::USoundManagerInstance()
{
	BGMSound1 = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMSound1"));
	BGMSound2 = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMSound2"));
	SFXSound = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXSound"));
	BGMSound1->bAutoActivate = false;
	BGMSound2->bAutoActivate = false;
	SFXSound->bAutoActivate = false;

	isPlayBGM = false;
	crruentPlayBGMAudioIndex = 0;
}

void USoundManagerInstance::PlayBGM(USoundBase* soundToPlay, TArray<bool> checkArray)
{
	if (isPlayBGM)
	{
		switch (crruentPlayBGMAudioIndex)
		{
			case 0:
				BGMSound2->SetSound(soundToPlay);
				for (int i = 0; i < checkArray.Num(); i++)
				{
					BGMSound2->SetBoolParameter("Num" + (i + 1), checkArray[i]);
				}
				BGMSound1->FadeOut(1.f, 0.f);
				BGMSound2->FadeIn(1.f, 1.f);
				BGMSound2->Play();
				break;
			case 1:
				BGMSound1->SetSound(soundToPlay);
				for (int i = 0; i < checkArray.Num(); i++)
				{
					BGMSound1->SetBoolParameter("Num" + (i + 1), checkArray[i]);
				}
				BGMSound2->FadeOut(1.f, 0.f);
				BGMSound1->FadeIn(1.f, 1.f);
				BGMSound1->Play();
				break;
		}
	}
	else
	{
		BGMSound1->SetSound(soundToPlay);
		for (int i = 0; i < checkArray.Num(); i++)
		{
			BGMSound1->SetBoolParameter("Num1", true);
		}
		BGMSound1->SetBoolParameter("Num1", true);
		BGMSound1->SetBoolParameter("Num2", true);
		BGMSound1->SetBoolParameter("Num3", true);
		BGMSound1->SetBoolParameter("Num4", true);
		BGMSound1->FadeIn(1.f, 1.f);
		BGMSound1->Play();
	}
}

void USoundManagerInstance::PlaySFX(USoundBase* soundToPlay)
{
	SFXSound->SetSound(soundToPlay);
	SFXSound->Play();
}
