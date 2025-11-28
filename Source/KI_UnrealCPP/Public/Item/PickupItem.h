// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupActor.h"
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

	inline void SetItemCount(int32 InCount) { Quantity = InCount; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Database")
	TObjectPtr<class UItemDataAsset> ItemDatabase = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	//EItemCode PickupItem = EItemCode::Gem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	int32 Quantity = 1;
};
