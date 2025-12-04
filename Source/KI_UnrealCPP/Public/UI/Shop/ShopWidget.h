// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void InitializeShopWidget(class UInventoryComponent* InventoryComponent);

	UFUNCTION()
	void PlayOpen();

	UFUNCTION()
	void PlayClose();

	void RequestSellItem(int32 InSlotIndex, int32 InPrice);

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OpenAndClose = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UShopItemSellWidget> ItemSellArea = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;
};
