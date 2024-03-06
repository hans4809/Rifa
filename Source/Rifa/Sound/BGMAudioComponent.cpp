// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMAudioComponent.h"
#include "Data/MyGameInstance.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UBGMAudioComponent::UBGMAudioComponent()
{
    PrimaryComponentTick.bCanEverTick = true;


    Sounds = TArray<USoundBase*>();
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder1(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_01.BGM_01'"));
    if (ObjectFinder1.Succeeded())
        Sounds.Add(ObjectFinder1.Object);
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder2(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_02.BGM_02'"));
    if (ObjectFinder2.Succeeded())
        Sounds.Add(ObjectFinder2.Object);
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder3(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_03.BGM_03'"));
    if (ObjectFinder3.Succeeded())
        Sounds.Add(ObjectFinder3.Object);
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder4(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_04.BGM_04'"));
    if (ObjectFinder4.Succeeded())
        Sounds.Add(ObjectFinder4.Object);
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder5(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_05.BGM_05'"));
    if (ObjectFinder5.Succeeded())
        Sounds.Add(ObjectFinder5.Object);
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder6(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_06.BGM_06'"));
    if (ObjectFinder6.Succeeded())
        Sounds.Add(ObjectFinder6.Object);
    static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder7(TEXT("/Script/Engine.SoundCue'/Game/Sounds/BGM_07.BGM_07'"));
    if (ObjectFinder7.Succeeded())
        Sounds.Add(ObjectFinder7.Object);
}

void UBGMAudioComponent::CrossfadeSound()
{
    // ���� ���带 ��� ���� ����� ������Ʈ�� ��ȿ�� ��쿡�� ����
    if (BgmAudioPrevious)
    {
        // ���� ������ ������ ������ ���̴� �ִϸ��̼� ����
        BgmAudioPrevious->FadeOut(CrossfadeDuration, 0.0f);
    }

    // ���ο� ���带 ����� ����� ������Ʈ ����
    BgmAudioNew = UGameplayStatics::SpawnSoundAttached(SoundToPlay, GetWorld()->GetFirstPlayerController()->GetRootComponent());

    BgmRefresh();
    // ���ο� ������ ������ ������ �ø��� �ִϸ��̼� ����
    BgmAudioNew->FadeIn(CrossfadeDuration, 1.0f);
    if (BgmAudioPrevious)
    {
        BgmAudioPrevious->DestroyComponent();
    }
    BgmAudioPrevious = BgmAudioNew;
}

void UBGMAudioComponent::PlayBgm()
{
    CrossfadeDuration = 1.f;
    if(RifaGameInstance == nullptr)
        RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    BgmSetting();
    CrossfadeSound();
}

void UBGMAudioComponent::BgmSetting()
{
    FString soundTrack;
    if (RifaGameInstance->SoundTrack.IsEmpty())
    {
        soundTrack = "Bgm1";
        RifaGameInstance->SoundTrack = "Bgm1";
    }
    else
        soundTrack = RifaGameInstance->SoundTrack;
        

    if (soundTrack == "Bgm1")
    {
        SoundToPlay = Sounds[0];
        CheckArray = TArray<EItem>{EItem::Piano_1_Medium, 
            EItem::WindInstrument_1_Medium , 
            EItem::Bell_1_High , 
            EItem::Piano_1_High
        };
    }
    else if (soundTrack == "Bgm2")
    {
        SoundToPlay = Sounds[1];
        CheckArray = TArray<EItem>{ EItem::StringInstrument_1_Medium,
            EItem::Piano_2_Low ,
            EItem::WindInstrument_2_Medium ,
            EItem::PercussionInstrument_1_Low,
            EItem::StringInstrument_2_Medium,
            EItem::Piano_2_High,
            EItem::StringInstrument_3_High,
            EItem::Bell_2_High
        };
    }
    else if (soundTrack == "Bgm3")
    {
        SoundToPlay = Sounds[2];
        CheckArray = TArray<EItem>{ EItem::Piano_1_Medium,
            EItem::WindInstrument_1_Medium ,
            EItem::Bell_1_High ,
            EItem::Voice_1_Women
        };
    }
    else if (soundTrack == "Bgm4")
    {
        SoundToPlay = Sounds[3];
        CheckArray = TArray<EItem>{ EItem::WindInstrument_2_Medium,
            EItem::Voice_2_Men ,
            EItem::Piano_2_High ,
            EItem::StringInstrument_3_High ,
            EItem::Bell_2_High ,
            EItem::StringInstrument_4_High
        };
    }
    else if (soundTrack == "Bgm5")
    {
        SoundToPlay = Sounds[4];
        CheckArray = TArray<EItem>{ EItem::Piano_1_Medium,
            EItem::WindInstrument_1_Medium ,
            EItem::Piano_1_High
        };
    }
    else if (soundTrack == "Bgm6")
    {
        SoundToPlay = Sounds[5];
        CheckArray = TArray<EItem>{ EItem::Voice_1_Women,
            EItem::WindInstrument_2_Medium ,
            EItem::Voice_2_Men ,
            EItem::PercussionInstrument_1_Low ,
            EItem::StringInstrument_2_Medium ,
            EItem::Bell_2_High ,
            EItem::PercussionInstrument_3_High
        };
    }
    else if (soundTrack == "Bgm7")
    {
        SoundToPlay = Sounds[6];
        CheckArray = TArray<EItem>{ EItem::WindInstrument_1_Medium,
            EItem::Bell_1_High ,
            EItem::StringInstrument_1_Medium ,
            EItem::WindInstrument_2_Medium ,
            EItem::StringInstrument_2_Medium ,
            EItem::Piano_2_High
        };
    }
}

void UBGMAudioComponent::BgmRefresh()
{
    int cnt = 1;
    for (int i = 0; i < CheckArray.Num(); i++)
    {
        if (RifaGameInstance->SoundItemHavingMap[CheckArray[i]])//RifaGameInstance->EItemMap[CheckArray[i]])
        {
            Str = FString::Printf(TEXT("Num%d"), cnt);
            float a = 1.f;
            if (RifaGameInstance->SoundItemOnOffMap[CheckArray[i]])
                a = 1.f;
            else
                a = 0.f;
            BgmAudioNew->SetFloatParameter(*Str, a);
            cnt++;
        }
    }
}
