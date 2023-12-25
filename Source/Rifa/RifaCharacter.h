// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InteractionInterface.h"
#include "RifaCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_Dynamic);
UCLASS(config=Game)
class ARifaCharacter : public ACharacter, public IInteractionInterface
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InterAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hair", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CurrentHairMesh;
	UPROPERTY()
	UCharacterMovementComponent* RifaCharacterMovement;
	UPROPERTY()
	bool First = true;
public:
	ARifaCharacter();
	//Event 생성
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic PickupItem;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic NPCTalk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	int FlyEnergyValue;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly")
	float FlyHeight;
	UFUNCTION(BlueprintCallable)
	float GetFlyTime(int _FlyEnergyValue);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	int SwimEnergyValue;
	UFUNCTION(BlueprintCallable)
	float GetSwimTime(int _SwimEnergyValue);
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	float SwimHeight;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	FVector StartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	FVector SwimStartLocation;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Swim")
	bool IsSwimming;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Interaction")
	AActor* InteractionTargetActor;
	UFUNCTION()
	FHitResult SwimCheck();
	UFUNCTION()
	void Die(AActor* trap);
	UFUNCTION(BlueprintCallable)
	void EnableMouseCursor();
	UFUNCTION(BlueprintCallable)
	void DisableMouseCursor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class ARifaCharacterParts* CurrentHair;
	UFUNCTION(BlueprintCallable)
	void ChangeHairPart();
#pragma region InterfaceFunction
	// InteractionInterface 상속 때문에 override 선언
	UFUNCTION()
	virtual void UseAction() override;
	UFUNCTION()
	virtual void DropAction(AActor* DropToItem) override;
	UFUNCTION()
	virtual void OnInterAction(ARifaCharacter* InterActionCharacter) override;
#pragma endregion
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
	UFUNCTION(BlueprintCallable)
	void Respawn();
	UFUNCTION(BlueprintCallable)
	void GameStart();
	UFUNCTION(BlueprintCallable)
	void Dash();
	UFUNCTION(BlueprintCallable)
	void EndDash();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void EndPlay(EEndPlayReason::Type) override;
	//void OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION(BlueprintCallable)
	//void EndCompoenentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	UPROPERTY()
	FTimerHandle FlyTimer;
	UPROPERTY()
	class UMyGameInstance* RifaGameInstance;
	UPROPERTY()
	FTimerHandle SwimTimer;
	UPROPERTY()
	FTimerHandle WidgetAnimTimer;
	UFUNCTION()
	void AnimTimerFunc();
	UPROPERTY()
	bool InventoryOpen = false;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = true))
	TArray<IInteractionInterface*> InteractionInRange;
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

