// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "ReinforcedWeaponActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponDeprecated);

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API AReinforcedWeaponActor : public AWeaponActor
{
	GENERATED_BODY()

public:
	AReinforcedWeaponActor();
	virtual void BeginPlay() override;
	void ConsumeUsageCount();
	void WeaponThrown();

	inline void ChargeUsageCount() { UsageCount = 3; }

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnWeaponDeprecated OnWeaponDeprecated;

protected:
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	UFUNCTION()
	void EquipWeapon(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCapsuleComponent> WeaponEquipCollision = nullptr;

private:
	int32 UsageCount = 0;
};
