// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Data/MyGameInstance.h"
#include "RifaCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_Dynamic);
UCLASS(config=Game)
class ARifaCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlyAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwimAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InterAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	UPROPERTY()
	UCharacterMovementComponent* RifaCharacterMovement;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> HeadTrigger;
	bool First = true;
public:
	ARifaCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hair", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> CurrentHairMesh;
	//Event 생성
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic PickupItem;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic NPCTalk;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	int FlyEnergyNum;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly")
	float FlyHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	float FlyEnergyPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	float MaxFlyEnergyPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	FTimerHandle FlyTimer;
	UFUNCTION(BlueprintCallable)
	float GetFlyTime();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	int SwimEnergyNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float SwimEnergyPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float MaxSwimEnergyPercent;
	UFUNCTION(BlueprintCallable)
	float GetSwimTime();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	FTimerHandle SwimTimer;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	float SwimHeight;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	FVector StartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	FVector SwimStartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	bool bIsSwimming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bCanSwim;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bIsRideUpWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bIsRideDownWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bCanRideUpWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bCanRideDownWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	FRotator WaterFallRotation;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Swim")
	FVector WaterFallEndVector;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Swim")
	FVector WaterFallStartVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float ElapsedTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float WaterFallTime;
public:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Interaction")
	TObjectPtr<AActor> InteractionTargetActor;
	//UPROPERTY(EditAnywhere)
	//class UBGMAudioComponent* Bgm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	ECharacterMaterialItem ECurrentCharacterMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	EHairPartsItem ECurrentCharacterHairPart;
// Widget Part
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> GameSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGameSettingWidget> GameSettingWidgetAsset; 
	UFUNCTION(BlueprintCallable)
	void ReturnWalk();
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Fly();

	UFUNCTION(BlueprintCallable)
	void Swim();
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim", meta = (AllowPrivateAccess = true))
	bool IsFlying;
	UFUNCTION(BlueprintCallable)
	void EndSwim();
	UFUNCTION(BlueprintCallable)
	void Interaction();
	UFUNCTION(BlueprintCallable)
	void Dash();
	UFUNCTION(BlueprintCallable)
	void EndDash();
	UFUNCTION(BlueprintCallable)
	void Pause();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(EEndPlayReason::Type) override;
	std::pair<FHitResult, bool> LineHitResult(FVector DirectionVector, float LineLength, ECollisionChannel TraceChannel);
private:

	UPROPERTY()
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaGameMode> GameModeReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "State")
	bool bIsDied;
	UFUNCTION(BlueprintCallable)
	void OnHeadOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

