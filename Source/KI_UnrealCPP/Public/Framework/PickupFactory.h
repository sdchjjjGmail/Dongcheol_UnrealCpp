// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Item/PickupActor.h"
#include "PickupFactory.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UPickupFactory : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Pickup Factory")
	APickupActor* SpawnPickup(
		EItemCode InCode, 
		FVector InLocation = FVector::ZeroVector,
		FRotator InRotator = FRotator::ZeroRotator,
		FVector Velocity = FVector::ZeroVector);

protected:
	void LoadPickupClassesMap();

	UPROPERTY()
	TMap<EItemCode, TSubclassOf<APickupActor>> PickupClasses;

private:
	int32 TryCount = 0;
	TMap<EItemCode, int32> DropRateTestCount;
};
