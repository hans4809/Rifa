// Copyright Epic Games, Inc. All Rights Reserved.

#include "RifaCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PhysicsVolume.h"
#include "Data/RIFASaveGame.h"
#include "Gimmick/Trap.h"
#include "Gimmick/Switch.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/WidgetAnimation.h"
#include "Data/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Gimmick/RifaCharacterParts.h"
//#include "Sound/BGMAudioComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Widget/GameSettingWidget.h"
#include "Game/RifaGameMode.h"
#include "Widget/GameHUD.h"
#include "Components/SphereComponent.h"
#include <Gimmick/WaterActor.h>
#include <Gimmick/WaterFall.h>


//////////////////////////////////////////////////////////////////////////
// ARifaCharacter

ARifaCharacter::ARifaCharacter()
{
	bIsDied = false;
	PrimaryActorTick.bCanEverTick = true;

	HeadTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("HeadTrigger"));
	HeadTrigger->SetupAttachment(RootComponent);
	HeadTrigger->SetSphereRadius(23.f);
	HeadTrigger->SetCollisionProfileName(TEXT("Trigger"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCharacter"));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CurrentHairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	//CurrentHairMesh->SetupAttachment(GetMesh(), TEXT("hair_socket"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//Bgm = CreateDefaultSubobject<UBGMAudioComponent>(TEXT("BGM"));

	RifaCharacterMovement = GetCharacterMovement();
	FlyHeight = 100.f;
	SwimHeight = 100.f;
	JumpMaxCount = 2;
	bIsSwimming = false;
	IsFlying = false;
	//WaterForcingVector = FVector(0, 0, 0);
	FlyEnergyNum = 0;
	SwimEnergyNum = 0;
}

float ARifaCharacter::GetFlyTime()
{
	switch (FlyEnergyNum)
	{
		case 0:
			return 0.0f;
			break;
		case 1:
			return 2.0f;
			break;
		case 2:
			return 3.0f;
			break;
		case 3:
			return 4.0f;
			break;
		case 4:
			return 5.0f;
			break;
		default:
			return 60.0f;
			break;
	}
}

float ARifaCharacter::GetSwimTime()
{
	switch (SwimEnergyNum)
	{
		case 0:
			return 0.0f;
			break;
		case 1:
			return 3.0f;
			break;
		case 2:
			return 5.0f;
			break;
		case 3:
			return 7.0f;
			break;
		case 4:
			return 9.0f;
			break;
		default:
			return 11.0f;
			break;

	}
}

void ARifaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(FInputModeGameOnly());
	GameModeReference = Cast<ARifaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(RifaGameInstance)) 
	{
		ECurrentCharacterMaterial = RifaGameInstance->ECurrentCharacterMaterial;
		ECurrentCharacterHairPart = RifaGameInstance->ECurrentCharacterHairPart;

		GetMesh()->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[ECurrentCharacterMaterial]);
		CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[ECurrentCharacterHairPart]);

		if (ECurrentCharacterHairPart == EHairPartsItem::Default) 
		{
			CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[ECurrentCharacterMaterial]);
		}
		else 
		{
			CurrentHairMesh->SetMaterial(0, CurrentHairMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface);
		}
		const UEnum* HairPartEnum = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.EHairPartsItem"));
		FString EnumMetaData = HairPartEnum->GetDisplayNameTextByValue((int)ECurrentCharacterHairPart).ToString();
		if (EnumMetaData.Contains(TEXT("Default")))
		{
			CurrentHairMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_Default"));
		}
		else 
		{
			CurrentHairMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket_HairParts"));
		}
	}

	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARifaCharacter::OnHeadOverlapped);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	for (bool bFly : RifaGameInstance->FlyItemArr)
	{
		if (bFly) 
		{ 
			FlyEnergyNum++;
			MaxFlyEnergyPercent += 0.2;
		}
	}
	FlyEnergyPercent = MaxFlyEnergyPercent;

	for (bool bSwim : RifaGameInstance->SwimItemArr)
	{
		if (bSwim) 
		{ 
			SwimEnergyNum++; 
			MaxSwimEnergyPercent += 0.2;
		}
	}
	SwimEnergyPercent = MaxSwimEnergyPercent;
	//Bgm->PlayBgm();	
}

void ARifaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FlyEnergyNum != 0) 
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(FlyTimer))
		{
			FlyEnergyPercent = GetWorld()->GetTimerManager().GetTimerRemaining(FlyTimer) / GetFlyTime() * MaxFlyEnergyPercent;
		}
		else 
		{
			if (FlyEnergyPercent < MaxFlyEnergyPercent)
			{
				FlyEnergyPercent += DeltaTime * 0.1;
			}
		}

	}

	if (SwimEnergyNum != 0) 
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(SwimTimer))
		{
			SwimEnergyPercent = GetWorld()->GetTimerManager().GetTimerRemaining(SwimTimer) / GetSwimTime() * MaxSwimEnergyPercent;
		}
		else 
		{
			if (SwimEnergyPercent < MaxSwimEnergyPercent)
			{
				SwimEnergyPercent += DeltaTime * 0.1;
			}
		}

	}

	if (bIsSwimming) 
	{
		if (bIsRideUpWaterFall)
		{
			std::pair<FHitResult, bool> GroundHitResult = LineHitResult(-GetActorForwardVector(), 100.f, ECollisionChannel::ECC_Visibility);

			if (GroundHitResult.second) {
				bIsSwimming = false;
				bIsRideUpWaterFall = false;
				SetActorRotation(FRotator(0.f, 0.f, 0.f));
				GetCharacterMovement()->SetMovementMode(MOVE_Falling);
				GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
			}
		}
		else if (bIsRideDownWaterFall)
		{
			std::pair<FHitResult, bool> GroundHitResult = LineHitResult(GetActorForwardVector(), 100.f, ECollisionChannel::ECC_Visibility);

			if (GroundHitResult.second) {
				bIsSwimming = false;
				bIsRideDownWaterFall = false;
				SetActorRotation(FRotator(0.f, 0.f, 0.f));
				GetCharacterMovement()->SetMovementMode(MOVE_Falling);
				GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
			}
		}

		std::pair<FHitResult, bool> WaterHitResult = LineHitResult(-GetActorUpVector(), 500.f, ECollisionChannel::ECC_GameTraceChannel1);
		if (!WaterHitResult.second)
			ReturnWalk();
	}
}

void ARifaCharacter::EndPlay(EEndPlayReason::Type EndReason)
{
	Super::EndPlay(EndReason);
	PickupItem.Clear();
}

std::pair<FHitResult, bool> ARifaCharacter::LineHitResult(FVector DirectionVector, float LineLength, ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility)
{	
	FHitResult HitResult;
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = false;

	if (TraceChannel == ECollisionChannel::ECC_GameTraceChannel1)
	{
		bResult = GetWorld()->LineTraceMultiByChannel(
			OUT HitResults,
			GetActorLocation(),
			GetActorLocation() + DirectionVector * LineLength,
			TraceChannel,
			Params
		);

		if (bResult)
		{
			for (auto Hit : HitResults)
			{
				if (Cast<AWaterFall>(Hit.GetActor()))
				{
					HitResult = Hit;
					bResult = true;
					break;
				}
				else 
				{
					bResult = false;
				}
			}
		}
	}
	else
	{
		bResult = GetWorld()->LineTraceSingleByChannel(
			OUT HitResult,
			GetActorLocation(),
			GetActorLocation() + DirectionVector * LineLength,
			TraceChannel,
			Params
		);
	}

	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + DirectionVector * LineLength,
		DrawColor,
		false,
		2.f);

	return std::make_pair(HitResult, bResult);
}

void ARifaCharacter::Dash()
{
	RifaCharacterMovement->MaxWalkSpeed = 1000.f;
}

void ARifaCharacter::EndDash()
{
	RifaCharacterMovement->MaxWalkSpeed = 500.f;
}

void ARifaCharacter::Pause()
{
	if (IsValid(GameSettingWidgetClass))
	{
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
		GameSettingWidgetAsset = Cast<UGameSettingWidget>(CreateWidget(GetWorld(), GameSettingWidgetClass));
		GameSettingWidgetAsset->Init();
		CustomTimeDilation = 0.f;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARifaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Look);
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Started, this, &ARifaCharacter::Fly);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Pause);
		EnhancedInputComponent->BindAction(SwimAction, ETriggerEvent::Started, this, &ARifaCharacter::Swim);
		EnhancedInputComponent->BindAction(InterAction, ETriggerEvent::Completed, this, &ARifaCharacter::Interaction);
		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Dash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &ARifaCharacter::EndDash);
	}

}

void ARifaCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (bIsRideUpWaterFall || bIsRideDownWaterFall)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		return;
	}
	if (Controller != nullptr)
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		if (RifaCharacterMovement->IsFlying() && !bIsSwimming)
		{
			AddMovementInput(FollowCamera->GetForwardVector(), MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
		else
		{
			AddMovementInput(ForwardDirection, MovementVector.Y );
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void ARifaCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARifaCharacter::Fly()
{
	if (FlyEnergyNum == 0 || !RifaGameInstance->bCanFly) 
	{
		return;
	}
	if (!(RifaCharacterMovement->IsFlying()))
	{
		GetWorld()->GetTimerManager().SetTimer(FlyTimer, this, &ARifaCharacter::ReturnWalk, (FlyEnergyPercent / MaxFlyEnergyPercent) * ARifaCharacter::GetFlyTime(), false);
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		SetActorLocation(GetActorLocation() + FVector(0, 0, FlyHeight));
	}
	else 
	{
		GetWorld()->GetTimerManager().ClearTimer(FlyTimer);
		RifaCharacterMovement->SetMovementMode(MOVE_Falling);
	}
}


void ARifaCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (bIsDied)
	{
		return;
	}
	else if(RifaCharacterMovement->IsFalling())
	{
		UE_LOG(LogTemp, Log, TEXT("Falling Velocity : %f"), RifaCharacterMovement->Velocity.Z);
		if (RifaCharacterMovement->Velocity.Z <= -2000)
		{
			UE_LOG(LogTemp, Log, TEXT("Palyer Fall Die"));
			if (GameModeReference)
			{
				GameModeReference->PlayerDie(this);
			}
		}
		else
		{
			return;
		}
	}
}

void ARifaCharacter::OnHeadOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(Cast<AWaterActor>(OtherActor))) 
	{
		if (GameModeReference)
		{
			GameModeReference->PlayerDie(this);
		}
	}
}

void ARifaCharacter::Swim()
{
	if (SwimEnergyNum == 0 || !RifaGameInstance->bCanSwim)
	{
		return;
	}
	if (bCanSwim) // 그냥 수영
	{
		bIsSwimming = true;
		StartLocation = (GetActorLocation() - GetActorForwardVector() * 50);
		SetActorLocation(GetActorLocation() + GetActorUpVector() * 25 + GetActorForwardVector() * 50);
		RifaCharacterMovement->bCheatFlying = true;
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, (SwimEnergyPercent / MaxSwimEnergyPercent) * ARifaCharacter::GetSwimTime(), false);
	}
	//else if (bCanRideDownWaterFall) // 폭포 타고 내려가는 거
	//{
	//	
	//}
	else // 폭포 체크
	{
		std::pair<FHitResult, bool> FrontWaterHitResult = LineHitResult(GetActorForwardVector(), 300.f, ECollisionChannel::ECC_GameTraceChannel1);
		FRotator SwimRotation = FRotator::ZeroRotator;
		FVector SwimLocation = FVector::ZeroVector;
		if (FrontWaterHitResult.second) // 폭포를 타고 올라가는 것을 우선으로 체크
		{
			SwimRotation = FrontWaterHitResult.first.Component->GetOwner()->GetActorRotation() + FRotator(0, -90.f, 0);
			SwimLocation = FrontWaterHitResult.first.ImpactPoint - (GetActorForwardVector() * 300.f) + (GetActorUpVector() * 100.f);
			bIsRideUpWaterFall = true;
		}
		else 
		{
			FVector DirectionVector = (GetActorForwardVector() - GetActorUpVector());
			DirectionVector.Normalize();
			std::pair<FHitResult, bool> DiagnolWaterHitResult = LineHitResult(DirectionVector, 500.f, ECollisionChannel::ECC_GameTraceChannel1);
			if (!DiagnolWaterHitResult.second) // 폭포 타고 올라갈 곳이 없을 때 폭포 타고 내려갈 수 있는지 체크
			{
				return;
			}
			SwimRotation = DiagnolWaterHitResult.first.Component->GetOwner()->GetActorRotation() + FRotator(0, 90.f, 0);
			//SetActorRotation(WaterHitResult.first.Component->GetOwner()->GetActorRotation() + FRotator(0, 90.f, 0));
			//SetActorLocation(WaterHitResult.first.ImpactPoint + (GetActorForwardVector() * 300.f));
			SwimLocation = DiagnolWaterHitResult.first.ImpactPoint + (GetActorForwardVector() * 300.f);
			bIsRideDownWaterFall = true;
		}
		bIsSwimming = true;
		StartLocation = GetActorLocation();
		SetActorRotation(SwimRotation);
		SetActorLocation(SwimLocation);
		AddActorWorldRotation(FRotator(0, 0, -90.f));
		RifaCharacterMovement->bCheatFlying = true;
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, (SwimEnergyPercent / MaxSwimEnergyPercent) * ARifaCharacter::GetSwimTime(), false);
	}
}

void ARifaCharacter::ReturnWalk()
{
	if (bIsRideUpWaterFall)
	{
		SetActorLocationAndRotation(GetActorLocation() - GetActorUpVector() * 400.f + GetActorForwardVector() * 400.f, FRotator::ZeroRotator);
	}
	else
	{
		SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
	bIsSwimming = false;
	bIsRideUpWaterFall = false;
	bIsRideDownWaterFall = false;
	RifaCharacterMovement->bCheatFlying = false;
	RifaCharacterMovement->SetMovementMode(MOVE_Falling);
	GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
}

void ARifaCharacter::EndSwim()
{
	bIsSwimming = false;
	bIsRideUpWaterFall = false;
	bIsRideDownWaterFall = false;
	SetActorLocation(StartLocation);
	SetActorRotation(FRotator(0.f, 0.f, 0.f));
	RifaCharacterMovement->bCheatFlying = false;
	RifaCharacterMovement->SetMovementMode(MOVE_Falling);
	GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
}

void ARifaCharacter::Interaction()
{
	ASwitch* target = Cast<ASwitch>(InteractionTargetActor);
	if (target == nullptr) 
	{
		if (PickupItem.IsBound() == true) 
		{
			PickupItem.Broadcast();
		}
		if (NPCTalk.IsBound() == true)
		{
			NPCTalk.Broadcast();
		}
		return;
	}
	target->Interaction();
	target->DoWork();
}