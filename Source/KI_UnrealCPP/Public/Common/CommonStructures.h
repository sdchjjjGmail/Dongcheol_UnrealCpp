// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonEnums.h"
#include "CommonStructures.generated.h"

USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 DataA = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DataB = 15.5;
};

USTRUCT(BlueprintType)
struct FItemDropInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items")
	TSubclassOf<class APickupActor> DropItemClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items")
	float DropRate = 1.0f;
};

//USTRUCT(BlueprintType)
//struct PickupInfo
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
//	EItemCode PickupCode = EItemCode::BasicWeapon;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
//	TSubclassOf<class APickupActor> PickupClass = nullptr;
//
//};