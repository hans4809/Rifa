// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RifaCharacter.generated.h"


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
	UPROPERTY()
	UCharacterMovementComponent* RifaCharacterMovement;
	UPROPERTY()
	APhysicsVolume* PhysicsVolume;

public:
	ARifaCharacter();
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly", meta = (AllowPrivateAccess = true))
	float FlyHeight;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly", meta = (AllowPrivateAccess = true))
	float FlyTime;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim", meta = (AllowPrivateAccess = true))
	FVector StartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim", meta = (AllowPrivateAccess = true))
	FVector SwimStartLocation;
	UPROPERTY()
	FTimerHandle FlyTimer;
	UPROPERTY()
	FTimerHandle SwimTimer;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim", meta = (AllowPrivateAccess = true))
	bool IsSwimming;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	AActor* InteractionTargetActor;
	UFUNCTION()
	void Die(AActor* trap);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> ItemList;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Fly();
	UFUNCTION(BlueprintCallable)
	void Swim();
	UFUNCTION(BlueprintCallable)
	void ReturnWalk();
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim", meta = (AllowPrivateAccess = true))
	bool IsFlying;
	UFUNCTION(BlueprintCallable)
	void EndSwim();
	UFUNCTION(BlueprintCallable)
	void Interaction();
	UFUNCTION(BlueprintCallable)
	void Respawn();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

