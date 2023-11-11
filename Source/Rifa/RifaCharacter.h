// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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
	class UInputAction* InventoryAction;
	UPROPERTY()
	UCharacterMovementComponent* RifaCharacterMovement;
	UPROPERTY()
	APhysicsVolume* PhysicsVolume;
	UPROPERTY()
	bool First = true;
public:
	ARifaCharacter();
	//Event 생성
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic PickupItem;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly")
	float FlyHeight;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly")
	float FlyTime;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	FVector StartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	FVector SwimStartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	bool IsSwimming;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	AActor* InteractionTargetActor;
	UFUNCTION()
	void Die(AActor* trap);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> ItemList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float EnergyValue;
	UFUNCTION(BlueprintCallable)
	void EnableMouseCursor();
	UFUNCTION(BlueprintCallable)
	void DisableMouseCursor();
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UGameHUD* GameHUDWidget;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHUD> RifaHUDClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	class ARifaHUD* RifaHUD;
	UFUNCTION(BlueprintCallable)
	void Fly();
	UFUNCTION(BlueprintCallable)
	void OpenAndCloseInventory();
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
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void EndPlay(EEndPlayReason::Type) override;

private:
	UPROPERTY()
	FTimerHandle FlyTimer;
	UPROPERTY()
	FTimerHandle SwimTimer;
	UPROPERTY()
	FTimerHandle WidgetAnimTimer;
	UFUNCTION()
	void AnimTimerFunc();
	UPROPERTY()
	bool InventoryOpen = false;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UGameHUD* GetGameHUDReference() { return GameHUDWidget; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ARifaHUD* GetRifaHUDReference() { return RifaHUD; }
};

