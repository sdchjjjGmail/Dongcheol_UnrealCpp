// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupActor.h"
#include "PickupWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API APickupWeapon : public APickupActor
{
	GENERATED_BODY()

public:
	virtual void OnPickupComplete_Implementation() override;

	inline void SetWeaponUseCount(int32 InCount) { UseCount = InCount; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Weapon")
	EWeaponCode PickupWeapon = EWeaponCode::BasicWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Weapon")
	int32 UseCount = 1;
};
