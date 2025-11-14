// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AnimNotify/AnimNotifyState_SectionJump.h"
#include "AnimNotify/AnimNotifyState_ComboPractice.h"
#include "ActionCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponCollisionOn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponCollisionOff);

class UInputAction;
//class USpringArmComponent;
class UResourceComponent;
//class UAnimNotifyState_SectionJump;

UCLASS()
class KI_UNREALCPP_API AActionCharacter : public ACharacter
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

	UResourceComponent* GetResourceComponent() { return Resource; }

	void SetCollisionOn();
	void SetCollisionOff();

	inline void SetSectionJumpNotify(UAnimNotifyState_SectionJump* InSectionJumpNotify)
	{
		SectionJumpNotify = InSectionJumpNotify;
		bComboReady = InSectionJumpNotify != nullptr;
	}

	inline void SetComboSectionJumpNotify(UAnimNotifyState_ComboPractice* InComboSectionJumpNotify)
	{
		ComnoSectionJumpNotify = InComboSectionJumpNotify;
		bComboReady = InComboSectionJumpNotify != nullptr;
	}

protected:
	// 이동 방향 입력 받기
	void OnMoveInput(const FInputActionValue& InValue);

	// 구르기 입력 받기
	void OnRollInput(const FInputActionValue& InValue);

	// 공격 입력 받기
	void OnAttackInput(const FInputActionValue& InValue);

	// 달리기 모드 설정
	void SetSprintMode();

	// 걷기 모드 설정(다이나믹 델리게이트에 바인드하기 위해 UFUNCTION 추가)
	UFUNCTION()
	void SetWalkMode();

private:
	void SectionJumpForCombo();
	void SectionJumpForComboPractice();
	void SpendRunStamina(float InDeltaTime);

public:
	FOnWeaponCollisionOn OnWeaponCollisionOn;
	FOnWeaponCollisionOff OnWeaponCollisionOff;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<class USpringArmComponent> SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<class UCameraComponent> PlayerCamera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	TObjectPtr<class UResourceComponent> Resource = nullptr;

	// 인풋 액션들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move = nullptr;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Sprint = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Roll = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Attack = nullptr;

	// 달리기 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Movement")
	float SprintSpeed = 1200.0f;
	// 걷기 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Movement")
	float WalkSpeed = 600.0f;

	// 구르기 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> RollMontage = nullptr;
	// 공격 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;
	
	// 달리기 상태일 때 초당 스태미너 비용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	float SprintStaminaCost = 20.0f;

	// 구르기를 하기 위해 필요한 스태미너 비용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	float RollStaminaCost = 50.0f;
	// 공격을 하기 위해 필요한 스태미너 비용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	float AttackStaminaCost = 3.0f;
	
	// 플레이어가 뛰고 있는 중인지 표시 해놓은 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|State")
	bool bIsSprint = false;

	// 플레이어가 현재 가지고 있는 무기
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	TWeakObjectPtr<class AWeaponActor> CurrentWeapon = nullptr;
	
private:
	UPROPERTY()
	TWeakObjectPtr<UAnimInstance> AnimInstance = nullptr;

	// 현재 진행중인 섹션 점프 노티파이 스테이트
	UPROPERTY()
	TWeakObjectPtr<UAnimNotifyState_SectionJump> SectionJumpNotify = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UAnimNotifyState_ComboPractice> ComnoSectionJumpNotify = nullptr;
	
	// 콤보가 가능한 상황인지 확인하기 위한 플래그
	bool bComboReady = false;
};
