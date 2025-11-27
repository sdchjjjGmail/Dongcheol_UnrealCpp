// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Common/CommonEnums.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Type")
	EItemCode ItemType = EItemCode::Gem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Name")
	FName ItemName = FName(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Desc")
	FString ItemDescription = TEXT("");

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Icon")
	//Icon

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Price")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Stack")
	int32 Stack = 0;
};
