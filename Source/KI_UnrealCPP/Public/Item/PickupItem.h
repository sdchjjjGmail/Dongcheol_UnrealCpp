// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupActor.h"
#include "Data//ItemDataAsset.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API APickupItem : public APickupActor
{
	GENERATED_BODY()

public:
	virtual void OnPickupComplete_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Database")
	TObjectPtr<UItemDataAsset> ItemDatabase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Consumable")
	EItemCode PickupItem = EItemCode::Gem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Consumable")
	int32 Quantity = 1;
};
