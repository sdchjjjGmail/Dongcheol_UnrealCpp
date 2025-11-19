// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "Interface/Consumable.h"
#include "ConsumableWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUseEnded);

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API AConsumableWeapon : public AWeaponActor
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void OnAttack() override;
	virtual void OnWeaponPickedup(int32 InCount) override;
	virtual bool CanAttack() override { return RemainingUseCount > 0; }

	int32 GetRemainingUseCount() const { return RemainingUseCount; }

	//virtual FOnConsume& GetOnConsumeDelegate() {
	//	return OnWeaponUseEnded;
	//};

protected:
	virtual void OnWeaponActivate() override;
	virtual void OnWeaponDeActivate() override {};

protected:
	// 최대 사용 횟수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	int32 MaxUseCount = 3;
	
	// 남은 사용 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 RemainingUseCount = 0;

	// 무기를 다 사용했을 때 실행되는 델리게이트(현재 사용안함)
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "Weapon")
	FOnWeaponUseEnded OnWeaponUseEnded;
};
