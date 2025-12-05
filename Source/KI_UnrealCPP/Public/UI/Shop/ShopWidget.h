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
	
public:
	void InitializeShopWidget(class UInventoryComponent* InventoryComponent);

	UFUNCTION()
	void PlayOpen();

	UFUNCTION()
	void PlayClose();

	void RequestSellItem(int32 InSlotIndex, int32 InPrice);

protected:
	virtual void NativeConstruct() override;

	void ResetShopItemListWidget();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OpenAndClose = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UShopItemSellWidget> ItemSellArea = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UShopItemListWidget> ItemListWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Buy")
	TWeakObjectPtr<class UDataTable> ShopItemList = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TWeakObjectPtr<class UButton> Exit = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;
};
