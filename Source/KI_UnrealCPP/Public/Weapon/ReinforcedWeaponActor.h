// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "ReinforcedWeaponActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponDeprecated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponEquipCollision);

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

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnWeaponDeprecated OnWeaponDeprecated;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnWeaponEquipCollision OnWeaponEquipCollision;

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
	void ConsumeUsageCount();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCapsuleComponent> WeaponEquipCollision = nullptr;

private:
	int32 UsageCount = 0;
};
