// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemBuyWidget.generated.h"

class UImage;
class UTextBlock;
class UEditableTextBox;
class UButton;
class USizeBox;
/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UShopItemBuyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetItemData(class UItemDataAsset* InItemData, int32 InStockCount);

private:
	void InitShopState();

	UFUNCTION()
	void OnBuyItemCountTextChanged(const FText& Text);

	UFUNCTION()
	void OnBuyItemCountTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnPlayerBuyItem();

	void ShowSoldOut();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UImage> BuyItemIcon = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> BuyItemName = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> BuyItemPrice = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> BuyItemStockCount = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> BuyItemDesc = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> BuyItemCount = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UButton> ItemBuyButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<USizeBox> SoldoutPanel = nullptr;

private:
	static const int32 MinimumBuyItemCount = 1;

	UPROPERTY()
	UItemDataAsset* ItemData = nullptr;

	TWeakObjectPtr<class AActionCharacter> Player = nullptr;

	int32 StockCount = 0;
	int32 BuyCount = 0;
	//int32 Price = 0;
};
