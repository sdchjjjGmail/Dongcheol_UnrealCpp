// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "InputActionValue.h"
#include "ActionCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedDelegate, float, InStamina, float, InMaxStamina);

class UInputAction;
/**
 *
 */
UCLASS()
class CLASS_UNREAL_CPP_API AActionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void OnMoveInput(const FInputActionValue& InValue);
	void OnRollInput(const FInputActionValue& InValue);

	void SetSprintMode();
	void SetWalkMode();
	void ManageStamina();
	void DelayStaminaRestore();

	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<USkeletalMeshComponent> BodyMesh = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<class USpringArmComponent> SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<class UCameraComponent> PlayerCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Sprint = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Roll = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float NormalSpeed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float SprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	bool IsSprinting = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	bool IsStaminaRecovering = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	float MaxStamina = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	float Stamina = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	float RollStamina = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	float RestoreMultiplier = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	float StaminaSpendValue = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Value")
	float StaminaManagerSpeed = 0.05f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> RollMontage = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UAnimInstance> AnimInstance = nullptr;
	FTimerHandle timerHandle;

public:
	UPROPERTY(BlueprintAssignable, Category = "Player|Event")
	FOnStaminaChangedDelegate OnStaminaChanged;
};
