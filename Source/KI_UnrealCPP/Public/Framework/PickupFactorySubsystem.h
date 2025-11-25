// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Common/CommonEnums.h"
#include "PickupFactorySubsystem.generated.h"

//class UDataTable;
class APickupActor;

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UPickupFactorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void DropEnemyItem(UDataTable* DropItemTable, FVector DropLocation, FRotator DropRtation);

	void DropValidWeapon(TSubclassOf<APickupActor> PickupClass, 
		int32 RemainingUseCount, 
		FVector DropLocation,
		FRotator DropRtation,
		FVector velocity);

	void DropExpiredWeapon(EItemCode WeaponCode, FVector DropLocation, FRotator DropRotation);

protected:

};
