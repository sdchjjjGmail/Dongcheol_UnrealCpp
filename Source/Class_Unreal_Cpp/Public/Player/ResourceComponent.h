// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

// DELEGATE
// 그냥 Delegate vs DynamicDelegate
//  - DynamicDelegate는 블루프린트에서 사용 가능
//  - DynamicDelegate는 일반 Delegate에 비해 느리다.
//  - DynamicDelegate에는 람다식 추가가 불가능하다.
//  - DynamicDelegate에 바인딩 되는 함수는 UFUNCTION으로 선언되어야 한다.
// 
// 그냥 Delegate vs MulticastDelegate
//  - MulticastDelegate는 여러 리스너를 바인딩 할 수 있다.
// 
// Delegate vs Event
//  - Event는 외부에서 바인딩만 가능
//  - Delegate는 외부에서 바인딩과 실행 모두 가능
// 
// 선언은 클래스 외부에서 선언

// 선언은 서로 조합이 가능함
// DECLARE_DELEGATE
// DECLARE_DYNAMIC_DELEGATE 
// DECLARE_MULTICAST_DELEGATE
// DECLARE_DYNAMIC_MULTICAST_DELEGATE
// DECLARE_DELEGATE_RetVal
// DECLARE_DELEGATE_RetVal_OneParam

// FOnStaminaEmpty이름의 델리게이트가 있다라고 타입을 선언한 것
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaEmpty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, Stamina, float, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, Health, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLASS_UNREAL_CPP_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 스태미너 추가/감소용 함수
	UFUNCTION(BlueprintCallable)
	void AddStamina(float InValue);
	UFUNCTION(BlueprintCallable)
	void AddHealth(float InValue);

	inline float GetCurrentHealth() const { return Health; }
	inline float GetMaxHealth() const { return MaxHealth; }
	inline float GetCurrentStamina() const { return Stamina; }
	inline float GetMaxStamina() const { return MaxStamina; }

	//스태미너가 충분한지 확인하는 함수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool HasEnoughStamina(float InValue) const { return Stamina >= InValue; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool IsAlive() const { return Health > 0; }

public:
	// 스테미너가 다 떨어졌음을 알리는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaEmpty OnStaminaEmpty;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnDie OnDie;

private:
	void StaminaAutoRegenCoolTimerSet();
	void StaminaRegenPerTick();

	inline void SetCurrentHealth(float InValue) {
		Health = InValue;
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
	inline void SetCurrentStamina(float InValue) {
		Stamina = InValue;
		OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float MaxStamina = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float Stamina = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaRegenCooltime = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaRegenAmount = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float RollStamina = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float RestoreMultiplier = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaSpendValue = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaTickInterval = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Health")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Health")
	float Health = 0.0f;

private:
	FTimerHandle StaminaAutoRegenCoolTimer; // 스태미너 자동 회복용 타이머 핸들
	FTimerHandle StaminaRegenTickTimer; // 스태미너 자동 회복 시 틱별 타이머 핸들
};
