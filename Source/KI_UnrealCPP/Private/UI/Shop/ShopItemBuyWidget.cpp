// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemBuyWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Data/ItemDataAsset.h"
#include "Interface/InventoryOwner.h"

void UShopItemBuyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BuyItemCount)
	{
		BuyItemCount->SetHintText(FText::AsNumber(MinimumBuyItemCount));
		BuyItemCount->OnTextChanged.AddDynamic(this, &UShopItemBuyWidget::OnBuyItemCountTextChanged); // 변경이 있을 때
		BuyItemCount->OnTextCommitted.AddDynamic(this, &UShopItemBuyWidget::OnBuyItemCountTextCommitted); // 변경을 확정했을 때(엔터친 후, 포커스를 잃은 후)
	}
}

void UShopItemBuyWidget::OnBuyItemCountTextChanged(const FText& Text)
{
	FString number = Text.ToString();
	if (number.IsNumeric())
	{
		int32 count = FCString::Atoi(*number);
		BuyItemCount->SetText(FText::AsNumber(count));
	}
}

void UShopItemBuyWidget::OnBuyItemCountTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	FString number = Text.ToString();
	if (number.IsNumeric())
	{
		int32 count = FCString::Atoi(*number);
		BuyItemCount->SetText(FText::AsNumber(count));
	}
	else
	{
		BuyItemCount->SetText(FText::AsNumber(MinimumBuyItemCount));
	}
}
