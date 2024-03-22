// Copyright Epic Games, Inc. All Rights Reserved.

#include "RifaGameMode.h"
#include "Character/RifaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Widget/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Widget/FadeWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PhysicsVolume.h"


ARifaGameMode::ARifaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/RifaCharacters/BluePrints/BP_RifaCharacter_Final.BP_RifaCharacter_Final_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_GameHUD.WG_GameHUD_C'"));
	if (GameHUDWidget.Succeeded()) 
	{
		GameHUDWidgetClass = GameHUDWidget.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> FadeWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_FadeWidget.WG_FadeWidget_C'"));
	if (FadeWidget.Succeeded())
	{
		FadeWidgetClass = FadeWidget.Class;
	}
	CameraReference = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void ARifaGameMode::BeginPlay()
{
	Super::BeginPlay();
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GameInstanceReference = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(FadeWidgetClass))
	{
		FadeWidgetReference = Cast<UFadeWidget>(CreateWidget(GetWorld(), FadeWidgetClass));
	}
}


void ARifaGameMode::PlayerDie(ARifaCharacter* Player)
{
	Player->bIsDied = true;
	if (IsValid(FadeWidgetReference))
	{
		FadeWidgetReference->Init();
		FadeWidgetReference->PlayAnimation(FadeWidgetReference->FadeOut);
	}
	Player->DisableInput(Cast<APlayerController>(Player->Controller));
	//Player->GetCharacterMovement()->GravityScale = 0;
	//Player->GetCharacterMovement()->AddImpulse(FVector(0.f, 0.f, -100.f), true);
	Player->GetCharacterMovement()->SetMovementMode(MOVE_None);
	Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Player->GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = true;
	Player->GetFollowCamera()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	CameraReference = Player->GetFollowCamera();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARifaGameMode::PlayerRespawn, 2.f, false);
}

void ARifaGameMode::PlayerRespawn()
{
	auto Player = CharacterReference;
	CharacterReference->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//Player->GetCharacterMovement()->GravityScale = 1;
	Player->GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = false;
	if (IsValid(FadeWidgetReference))
	{
		FadeWidgetReference->Init();
		FadeWidgetReference->PlayAnimation(FadeWidgetReference->FadeIn);
	}
	CameraReference->AttachToComponent(Player->GetCameraBoom(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, USpringArmComponent::SocketName);
	//Player->EnableInput(Cast<APlayerController>(Player->Controller));
	if (GameInstanceReference->SavePosition != FVector(0, 0, 0))
	{
		Player->SetActorLocation(GameInstanceReference->SavePosition);
	}
	else 
	{
		Player->SetActorLocation(FindPlayerStart(Player->GetController())->GetActorLocation());
	}
	Player->bIsDied = false;
	Player->GetCharacterMovement()->bCheatFlying = false;
	Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}
