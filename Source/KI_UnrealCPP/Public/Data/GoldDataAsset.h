// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConsumableDataAsset.h"
#include "GoldDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UGoldDataAsset : public UConsumableDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Gold")
	int32 Amount = 100;

	virtual void Execute(AActor* InTarget) const override;
};
