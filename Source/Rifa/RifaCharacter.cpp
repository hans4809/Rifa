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


//////////////////////////////////////////////////////////////////////////
// ARifaCharacter

ARifaCharacter::ARifaCharacter()
{
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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	RifaCharacterMovement = GetCharacterMovement();
	PhysicsVolume = GetPhysicsVolume();
	FlyHeight = 100.f;
	FlyTime = 5.f;
	JumpMaxCount = 2;
	IsSwimming = false;
	IsFlying = false;
}

void ARifaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ARifaCharacter::Die(AActor* trap)
{
	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
	if (nullptr == RIFASaveGame)
	{
		RIFASaveGame = GetMutableDefault<URIFASaveGame>(); // Gets the mutable default object of a class.
	}
	Position = RIFASaveGame->SavePosition;
	ItemList = RIFASaveGame->ItemList;
	SetActorLocation(Position);
	UE_LOG(LogTemp, Log, TEXT("Die"));

	ATrap* Trap = Cast<ATrap>(trap);
	Trap->isDie = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARifaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Look);
		//EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Fly);
		//EnhancedInputComponent->BindAction(SwimAction, ETriggerEvent::Triggered, this, &ARifaCharacter::Swim);
		PlayerInputComponent->BindAction(TEXT("Fly"), EInputEvent::IE_Pressed, this, &ARifaCharacter::Fly);
		PlayerInputComponent->BindAction(TEXT("Swim"), EInputEvent::IE_Pressed, this, &ARifaCharacter::Swim);
		PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &ARifaCharacter::Interaction);
	}

}

void ARifaCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
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
	if (!(RifaCharacterMovement->IsFlying()))
	{
		GetWorld()->GetTimerManager().SetTimer(FlyTimer, this, &ARifaCharacter::ReturnWalk, FlyTime, false);
		RifaCharacterMovement->SetMovementMode(MOVE_Flying);
		SetActorLocation(GetActorLocation() + FVector(0, 0, FlyHeight));
	}
	else 
	{
		GetWorld()->GetTimerManager().ClearTimer(FlyTimer);
		RifaCharacterMovement->SetMovementMode(MOVE_Falling);
	}
}
void ARifaCharacter::Swim()
{
	IsSwimming = true;
	StartLocation = GetActorLocation();
	SetActorLocation(SwimStartLocation + GetActorUpVector() * FlyHeight);
	RifaCharacterMovement->bCheatFlying = true;
	RifaCharacterMovement->SetMovementMode(MOVE_Flying);
	GetWorld()->GetTimerManager().SetTimer(SwimTimer, this, &ARifaCharacter::EndSwim, FlyTime, false);
}

void ARifaCharacter::ReturnWalk()
{
	IsSwimming = false;
	ClientCheatWalk();
	RifaCharacterMovement->bCheatFlying = false;
	RifaCharacterMovement->SetMovementMode(MOVE_Falling);
	GetWorld()->GetTimerManager().ClearTimer(SwimTimer);
}

void ARifaCharacter::EndSwim()
{
	SetActorLocation(StartLocation);
	IsSwimming = false;
	ClientCheatWalk();
	RifaCharacterMovement->bCheatFlying = false;
	RifaCharacterMovement->SetMovementMode(MOVE_Walking);
}

void ARifaCharacter::Interaction()
{
	ASwitch* target = Cast<ASwitch>(InteractionTargetActor);
	if (target == nullptr)
		return;

	target->Interaction();
	target->DoWork();
}