// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupConsumable.h"
#include "ConsumableGold.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API AConsumableGold : public APickupConsumable
{
	GENERATED_BODY()

public:
	//virtual void OnPickupComplete_Implementation() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Gold = 100;

protected:
	virtual void OnConsume() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Gold")
	EItemCode PickupItemGold = EItemCode::Gold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Gold")
	int32 Amount = 0;
	
};
