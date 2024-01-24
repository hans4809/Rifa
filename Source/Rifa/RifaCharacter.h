// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InteractionInterface.h"
#include "MyGameInstance.h"
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
	class UInputAction* PauseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InterAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	UPROPERTY()
	UCharacterMovementComponent* RifaCharacterMovement;
	UPROPERTY()
	bool First = true;
public:
	ARifaCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hair", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* CurrentHairMesh;
	//Event 생성
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic PickupItem;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic NPCTalk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	int FlyEnergyNum;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Fly")
	float FlyHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	float FlyEnergyPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	FTimerHandle FlyTimer;
	UFUNCTION(BlueprintCallable)
	float GetFlyTime();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	int SwimEnergyNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float SwimEnergyPercent;
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
	bool IsSwimming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool IsWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bCanRideUpWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bCanRideDownWaterFall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	bool bCanSwim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	FVector WaterForcingVector;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Interaction")
	AActor* InteractionTargetActor;
	UPROPERTY(EditAnywhere)
	class UBGMAudioComponent* Bgm;
	UFUNCTION()
	FHitResult SwimCheck();
	UFUNCTION()
	void Die(AActor* trap);
	UFUNCTION(BlueprintCallable)
	void EnableMouseCursor();
	UFUNCTION(BlueprintCallable)
	void DisableMouseCursor();
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class ARifaCharacterParts* CurrentHair;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	ECharacterMaterialItem ECurrentCharacterMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	EHairPartsItem ECurrentCharacterHairPart;
	/*UFUNCTION(BlueprintCallable)
	void ChangeHairPart();*/	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> GameSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGameSettingWidget> GameSettingWidgetAsset;

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
	UFUNCTION(BlueprintCallable)
	void Pause();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(EEndPlayReason::Type) override;
	//void OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION(BlueprintCallable)
	//void EndCompoenentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:

	UPROPERTY()
	class UMyGameInstance* RifaGameInstance;
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
	/*UFUNCTION(BlueprintCallable)
	FORCEINLINE UGameHUD* GetGameHUDReference() { return GameHUDWidget; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ARifaHUD* GetRifaHUDReference() { return RifaHUD; }*/
	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaGameMode> GameModeReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "State")
	bool bIsDied;
};

