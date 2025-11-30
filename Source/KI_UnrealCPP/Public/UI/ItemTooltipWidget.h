// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ItemDataAsset.h"
#include "ItemTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UItemTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    void SetItemData(UItemDataAsset* InItemData, int32 InCount);

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* NameText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DescriptionText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* PriceText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CountText;
};
