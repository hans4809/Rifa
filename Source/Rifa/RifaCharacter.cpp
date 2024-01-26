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
#include "RIFASaveGame.h"
#include "Trap.h"
#include "Switch.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/WidgetAnimation.h"
#include "MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WaterFallComponent.h"
#include "RifaCharacterParts.h"
#include "BGMAudioComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameSettingWidget.h"
#include "RifaGameMode.h"



//////////////////////////////////////////////////////////////////////////
// ARifaCharacter

ARifaCharacter::ARifaCharacter()
{
	bIsDied = false;
	PrimaryActorTick.bCanEverTick = true;
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

	Bgm = CreateDefaultSubobject<UBGMAudioComponent>(TEXT("BGM"));

	RifaCharacterMovement = GetCharacterMovement();
	FlyHeight = 100.f;
	SwimHeight = 100.f;
	JumpMaxCount = 2;
	IsSwimming = false;
	IsFlying = false;
	WaterForcingVector = FVector(0, 0, 0);
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

float ARifaCharacter::GetSwimTime()
{
	switch (SwimEnergyNum)
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
			return 6.0f;
			break;

	}
}

void ARifaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(FInputModeGameOnly());
	CurrentHairMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hair_socket"));
	GameModeReference = Cast<ARifaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(RifaGameInstance)) 
	{
		ECurrentCharacterMaterial = RifaGameInstance->ECurrentCharacterMaterial;
		ECurrentCharacterHairPart = RifaGameInstance->ECurrentCharacterHairPart;

		GetMesh()->SetMaterial(0, RifaGameInstance->CharacterMaterialMap[ECurrentCharacterMaterial]);

		CurrentHairMesh->SetSkeletalMesh(RifaGameInstance->HairPartsMeshMap[ECurrentCharacterHairPart]);
		CurrentHairMesh->SetMaterial(0, RifaGameInstance->HairMaterialMap[ECurrentCharacterMaterial]);
	}

	//Add Input Mapping Context
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
	SwimEnergyPercent = MaxFlyEnergyPercent;

	//GameStart();

	Bgm->PlayBgm();	
}

void ARifaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FlyEnergyNum != 0) 
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(FlyTimer))
		{
			FlyEnergyPercent = GetWorld()->GetTimerManager().GetTimerRemaining(FlyTimer) / GetFlyTime();
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
			SwimEnergyPercent = GetWorld()->GetTimerManager().GetTimerRemaining(SwimTimer) / GetSwimTime();
		}
		else 
		{
			if (SwimEnergyPercent < MaxSwimEnergyPercent)
			{
				SwimEnergyPercent += DeltaTime * 0.1;
			}
		}

	}

	if (IsSwimming) 
	{
		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, false, this);
		float CollisionRange = 500.f;
		bool bResult = GetWorld()->LineTraceSingleByChannel(
			OUT HitResult,
			GetActorLocation(),
			GetActorLocation() - GetActorUpVector() * CollisionRange,
			ECollisionChannel::ECC_GameTraceChannel1,
			Params
		);
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			GetActorLocation() - GetActorUpVector() * CollisionRange,
			DrawColor,
			false,
			2.f);
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		RifaCharacterMovement->AddInputVector(FVector(WaterForcingVector.X / 2, WaterForcingVector.Y / 2, 0));
		if (bResult == false) {
			ReturnWalk();
		}
	}
}

void ARifaCharacter::EndPlay(EEndPlayReason::Type EndReason)
{
	Super::EndPlay(EndReason);
	PickupItem.Clear();
}

//void ARifaCharacter::OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (Cast<IInteractionInterface>(OtherActor)) 
//	{
//		InteractionInRange.AddUnique(Cast<IInteractionInterface>(OtherActor));
//	}
//	else 
//	{
//		for (UActorComponent* var : OtherActor->GetComponentsByInterface(UInteractionInterface::StaticClass()))
//		{
//			InteractionInRange.AddUnique(Cast<IInteractionInterface>(var));
//		}
//	}
//}
//
//void ARifaCharacter::EndCompoenentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (Cast<IInteractionInterface>(OtherActor))
//	{
//		InteractionInRange.Remove(Cast<IInteractionInterface>(OtherActor));
//	}
//	else
//	{
//		for (UActorComponent * var : OtherActor->GetComponentsByInterface(UInteractionInterface::StaticClass()))
//		{
//			InteractionInRange.Remove(Cast<IInteractionInterface>(var));
//		}
//	}
//}

void ARifaCharacter::Die(AActor* trap)
{
	//SetActorLocation(Position);
	UE_LOG(LogTemp, Log, TEXT("Die"));

	ATrap* Trap = Cast<ATrap>(trap);
	Trap->isDie = false;
}

//void ARifaCharacter::Save()
//{
//	URIFASaveGame* NewPlayerData = NewObject<URIFASaveGame>();
//	NewPlayerData->SavePosition = Position;
//	NewPlayerData->ItemList = ItemList;
//	NewPlayerData->SoundTrack = SoundTrack;
//
//	UGameplayStatics::SaveGameToSlot(NewPlayerData, "RIFASaveFile", 0);
//}

//void ARifaCharacter::Load()
//{
//	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
//	if (nullptr == RIFASaveGame)
//	{
//		RIFASaveGame = GetMutableDefault<URIFASaveGame>(); // Gets the mutable default object of a class.
//	}
//	Position = RIFASaveGame->SavePosition;
//	ItemList = RIFASaveGame->ItemList;
//	SoundTrack = RIFASaveGame->SoundTrack;
//}

void ARifaCharacter::Respawn()
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == this)
	{
		//SetActorLocation(Position);
	}
}

void ARifaCharacter::GameStart()
{
	//Load();
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == this)
	{
		//SetActorLocation(Position);
	}
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
	}
}

void ARifaCharacter::EnableMouseCursor()
{
	Cast<APlayerController>(Controller)->SetInputMode(FInputModeGameAndUI());
	//if (RifaHUD != nullptr) {
	//	RifaHUD->ShowCrossHair = false;
	//}
	Cast<APlayerController>(Controller)->bShowMouseCursor = true;
}

void ARifaCharacter::DisableMouseCursor()
{
	Cast<APlayerController>(Controller)->SetInputMode(FInputModeGameOnly());
	//if (RifaHUD != nullptr) {
	//	RifaHUD->ShowCrossHair = true;
	//}
	Cast<APlayerController>(Controller)->bShowMouseCursor = false;
}

//void ARifaCharacter::ChangeHairPart()
//{
//	if (CurrentHair)
//	{
//		//auto tempMesh = CurrentHairMesh->GetSkeletalMeshAsset();
//		//auto tempMaterial = CurrentHairMesh->GetSkeletalMeshAsset()->GetMaterials()[0].MaterialInterface;
//		auto tempHairPart = CurrentHairPart;
//		CurrentHairMesh->SetSkeletalMesh(CurrentHair->Mesh->GetSkeletalMeshAsset());
//		RifaGameInstance->CurrentCharacterHairPart = CurrentHairPart;
//		CurrentHairMesh->SetMaterial(0, CurrentHair->Mesh->GetMaterial(0));
//		CurrentHair->Mesh->SetSkeletalMeshAsset(tempMesh);
//		RifaGameInstance->CurrentHairPart[CurrentHair->ThisHairPart] = CurrentHair->Mesh->GetSkeletalMeshAsset();
//		CurrentHair->Mesh->SetMaterial(0, tempMaterial);
//	}
//}



void ARifaCharacter::UseAction()
{
	return;
}

void ARifaCharacter::DropAction(AActor* DropToItem)
{
	return;
}

void ARifaCharacter::OnInterAction(ARifaCharacter* InterActionCharacter)
{
	return;
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
		//PlayerInputComponent->BindAction(TEXT("Fly"), EInputEvent::IE_Pressed, this, &ARifaCharacter::Fly);
		//PlayerInputComponent->BindAction(TEXT("Swim"), EInputEvent::IE_Pressed, this, &ARifaCharacter::SwimCheck);
		//PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &ARifaCharacter::Interaction);
	}

}

void ARifaCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	
	if (InventoryOpen) {
		return;
	}
	if (IsWaterFall)
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
		//UE_LOG(LogTemp, Log, TEXT("ForwardDierction : %s\n FowardVector : %s"), *ForwardDirection.ToString(), *GetActorForwardVector().ToString());
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		if (RifaCharacterMovement->IsFlying() && !IsSwimming)
		{
			AddMovementInput(FollowCamera->GetForwardVector(), MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
		else if (IsSwimming && !IsWaterFall) 
		{
			const float Dot = FVector::DotProduct(GetActorForwardVector(), WaterForcingVector);
			const float ACosAngle = FMath::Acos(Dot);
			const float Angle = FMath::RadiansToDegrees(ACosAngle);
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
			if (Angle <= 90) 
			{
				RifaCharacterMovement->MaxFlySpeed = 1000;
			}
			else 
			{
				RifaCharacterMovement->MaxFlySpeed = 600;
			}
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
	if (InventoryOpen) {
		return;
	}
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARifaCharacter::Fly()
{
	if (InventoryOpen || FlyEnergyNum == 0) {
		return;
	}
	if (!(RifaCharacterMovement->IsFlying()))
	{
		GetWorld()->GetTimerManager().SetTimer(FlyTimer, this, &ARifaCharacter::ReturnWalk, FlyEnergyPercent * ARifaCharacter::GetFlyTime(), false);
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		SetActorLocation(GetActorLocation() + FVector(0, 0, FlyHeight));
	}
	else 
	{
		GetWorld()->GetTimerManager().ClearTimer(FlyTimer);
		RifaCharacterMovement->SetMovementMode(MOVE_Falling);
	}
}

void ARifaCharacter::OpenAndCloseInventory()
{
	/*if (GameHUDWidget->GetActivateInventory()) 
	{
		if (First) {
			GameHUDWidget->SetInventoryVisible(ESlateVisibility::Visible);
			First = false;
			EnableMouseCursor();
			GameHUDWidget->PlayAnimation(GameHUDWidget->MenuAnim);
			InventoryOpen = true;
		}
		else {
			GameHUDWidget->PlayAnimationReverse(GameHUDWidget->MenuAnim);
			if(WidgetAnimTimer.IsValid())
			{
				GetWorld()->GetTimerManager().ClearTimer(WidgetAnimTimer);
			}
			GetWorld()->GetTimerManager().SetTimer(WidgetAnimTimer, this, &ARifaCharacter::AnimTimerFunc, GameHUDWidget->MenuAnim->GetEndTime(), false);
		}
	}*/
}

FHitResult ARifaCharacter::SwimCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	float CollisionRange = 1500.f;

	bool bResult = GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * CollisionRange,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * CollisionRange,
		DrawColor,
		false,
		2.f);
	if (bResult)
	{
		for (auto obj : HitResult.GetActor()->GetComponents()) {
		}
		SwimStartLocation = HitResult.Location;
	}
	return HitResult;
}

void ARifaCharacter::AnimTimerFunc()
{
	/*GameHUDWidget->SetInventoryVisible(ESlateVisibility::Hidden);
	DisableMouseCursor();
	First = true;
	InventoryOpen = false;*/
}

void ARifaCharacter::Landed(const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Falling Velocity : %f"), RifaCharacterMovement->Velocity.Z);
	if (RifaCharacterMovement->Velocity.Z <= -1000)
	{
		UE_LOG(LogTemp, Log, TEXT("Palyer Fall Die"));
		if (!GameModeReference.IsNull()) 
		{
			GameModeReference->PlayerDie(this);
		}
	}
	else 
	{
		return;
	}
}

void ARifaCharacter::Swim()
{
	if (InventoryOpen || SwimEnergyNum == 0) {
		return;
	}
	//FHitResult HitResult = SwimCheck();
	//if (HitResult.GetActor()->IsValidLowLevel() && HitResult.GetActor()->GetName().Contains(TEXT("Water"))) 
	//{
	//	IsSwimming = true;
	//	StartLocation = GetActorLocation();
	//	if (HitResult.GetActor()->GetName().Contains(TEXT("WaterFall")))
	//	{
	//		IsWaterFall = true;
	//		AddActorWorldRotation(FRotator(0, 0, -90));
	//		//SetActorLocation(SwimStartLocation + getactor * SwimHeight);
	//	}
	//	else 
	//	{
	//		SetActorLocation(SwimStartLocation + GetActorUpVector() * SwimHeight);
	//	}
	//	RifaCharacterMovement->bCheatFlying = true;
	//	RifaCharacterMovement->SetMovementMode(MOVE_Flying);
	//	GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, ARifaCharacter::GetSwimTime(SwimEnergyValue), false);
	//}
	if (bCanSwim) 
	{
		IsSwimming = true;
		StartLocation = GetActorLocation();
		SetActorLocation(GetActorLocation() + GetActorUpVector() * 100 + GetActorForwardVector() * 50);
		RifaCharacterMovement->bCheatFlying = true;
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, SwimEnergyPercent * ARifaCharacter::GetSwimTime(), false);
	}
	else if (bCanRideUpWaterFall)
	{
		IsSwimming = true;
		IsWaterFall = true;
		StartLocation = GetActorLocation();
		AddActorWorldRotation(FRotator(0, 0, -90));
		RifaCharacterMovement->bCheatFlying = true;
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, SwimEnergyPercent * ARifaCharacter::GetSwimTime(), false);
	}
	else if (bCanRideDownWaterFall) 
	{
		IsSwimming = true;
		IsWaterFall = true;
		StartLocation = GetActorLocation();
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * 300);
		AddActorWorldRotation(FRotator(0, 0, -90));
		RifaCharacterMovement->bCheatFlying = true;
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, SwimEnergyPercent * ARifaCharacter::GetSwimTime(), false);
	}
}

void ARifaCharacter::ReturnWalk()
{
	IsSwimming = false;
	IsWaterFall = false;
	RifaCharacterMovement->MaxFlySpeed = 600;
	SetActorRotation(FRotator(0.f, 0.f, 0.f));
	ClientCheatWalk();
	RifaCharacterMovement->bCheatFlying = false;
	RifaCharacterMovement->SetMovementMode(MOVE_Walking);
	GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
}

void ARifaCharacter::EndSwim()
{
	IsSwimming = false;
	IsWaterFall = false;
	RifaCharacterMovement->MaxFlySpeed = 600;
	SetActorLocation(StartLocation);
	SetActorRotation(FRotator(0.f, 0.f, 0.f));
	ClientCheatWalk();
	RifaCharacterMovement->bCheatFlying = false;
	RifaCharacterMovement->SetMovementMode(MOVE_Walking);
	GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
}

void ARifaCharacter::Interaction()
{
	if (InventoryOpen) {
		return;
	}
	ASwitch* target = Cast<ASwitch>(InteractionTargetActor);
	if (target == nullptr) 
	{
		if (PickupItem.IsBound() == true) 
		{
			PickupItem.Broadcast();
			if (NPCTalk.IsBound() == true)
				NPCTalk.Broadcast();
		}
		return;
	}

	target->Interaction();
	target->DoWork();
}