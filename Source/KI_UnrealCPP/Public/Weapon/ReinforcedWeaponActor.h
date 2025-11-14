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
	virtual void BeginPlay() override;

	FOnWeaponDeprecated OnWeaponDeprecated;

protected:
	virtual void OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void StartOwnerSearch() override;

private:
	void ConsumeUsageCount();

private:
	int32 UsageCount = 0;
};
