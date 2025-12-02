// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Data/ItemDataAsset.h"
#include "IventoryDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UIventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	int32 Index = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	int32 ItemQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	TWeakObjectPtr<UItemDataAsset> ItemData = nullptr;
};
