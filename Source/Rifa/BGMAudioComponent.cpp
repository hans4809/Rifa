// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMAudioComponent.h"
#include "MyGameInstance.h"
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
    UE_LOG(LogTemp, Log, TEXT("Hi3"));
    // 이전 사운드를 재생 중인 오디오 컴포넌트가 유효한 경우에만 실행
    if (BgmAudioPrevious)
    {
        // 이전 사운드의 볼륨을 서서히 줄이는 애니메이션 설정
        BgmAudioPrevious->FadeOut(CrossfadeDuration, 0.0f);
    }

    // 새로운 사운드를 재생할 오디오 컴포넌트 생성
    BgmAudioNew = UGameplayStatics::SpawnSoundAttached(SoundToPlay, GetWorld()->GetFirstPlayerController()->GetRootComponent());

    int cnt = 1;
    for (int i = 0; i < CheckArray.Num(); i++)
    {
        if (true)//RifaGameInstance->ItemMap[CheckArray[i]])
        {
            Str = FString::Printf(TEXT("Num%d"), cnt);
            BgmAudioNew->SetBoolParameter(*Str, true);
            cnt++;
        }
    }

    // 새로운 사운드의 볼륨을 서서히 늘리는 애니메이션 설정
    BgmAudioNew->FadeIn(CrossfadeDuration, 1.0f);
    if (BgmAudioPrevious)
    {
        BgmAudioPrevious->DestroyComponent();
    }
    BgmAudioPrevious = BgmAudioNew;
}

void UBGMAudioComponent::PlayBgm()
{
    CrossfadeDuration = 3.f;
    if(RifaGameInstance == nullptr)
        RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    BgmSetting();
    CrossfadeSound();
}

void UBGMAudioComponent::BgmSetting()
{
    FString soundTrack = RifaGameInstance->SoundTrack;

    if (soundTrack == "Bgm1")
    {
        SoundToPlay = Sounds[0];
        CheckArray = TArray<Item>{Item::Piano_1_Medium, 
            Item::WindInstrument_1_Medium , 
            Item::Bell_1_High , 
            Item::Piano_1_High
        };
    }
    else if (soundTrack == "Bgm2")
    {
        SoundToPlay = Sounds[1];
        CheckArray = TArray<Item>{ Item::StringInstrument_1_Medium,
            Item::Piano_2_Low ,
            Item::WindInstrument_2_Medium ,
            Item::PercussionInstrument_1_Low,
            Item::StringInstrument_2_Medium,
            Item::Piano_2_High,
            Item::StringInstrument_3_High,
            Item::Bell_2_High
        };
    }
    else if (soundTrack == "Bgm3")
    {
        SoundToPlay = Sounds[2];
        CheckArray = TArray<Item>{ Item::Piano_1_Medium,
            Item::WindInstrument_1_Medium ,
            Item::Bell_1_High ,
            Item::Voice_1_Women
        };
    }
    else if (soundTrack == "Bgm4")
    {
        SoundToPlay = Sounds[3];
        CheckArray = TArray<Item>{ Item::WindInstrument_2_Medium,
            Item::Voice_2_Men ,
            Item::Piano_2_High ,
            Item::StringInstrument_3_High ,
            Item::Bell_2_High ,
            Item::StringInstrument_4_High
        };
    }
    else if (soundTrack == "Bgm5")
    {
        SoundToPlay = Sounds[4];
        CheckArray = TArray<Item>{ Item::Piano_1_Medium,
            Item::WindInstrument_1_Medium ,
            Item::Piano_1_High
        };
    }
    else if (soundTrack == "Bgm6")
    {
        SoundToPlay = Sounds[5];
        CheckArray = TArray<Item>{ Item::Voice_1_Women,
            Item::WindInstrument_2_Medium ,
            Item::Voice_2_Men ,
            Item::PercussionInstrument_1_Low ,
            Item::StringInstrument_2_Medium ,
            Item::Bell_2_High ,
            Item::PercussionInstrument_3_High
        };
    }
    else if (soundTrack == "Bgm7")
    {
        SoundToPlay = Sounds[6];
        CheckArray = TArray<Item>{ Item::WindInstrument_1_Medium,
            Item::Bell_1_High ,
            Item::StringInstrument_1_Medium ,
            Item::WindInstrument_2_Medium ,
            Item::StringInstrument_2_Medium ,
            Item::Piano_2_High
        };
    }
}