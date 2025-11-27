// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupActor.h"
#include "PickupConsumable.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API APickupConsumable : public APickupActor
{
	GENERATED_BODY()
	
public:
	virtual void OnPickupComplete_Implementation() override;

protected:
	virtual void OnConsume();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Consumable")
	EItemCode PickupItem = EItemCode::PotionHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Consumable")
	int32 Quantity = 1;
};
