// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemBuyWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Data/ItemDataAsset.h"
#include "Interface/InventoryOwner.h"
#include <Player/ActionCharacter.h>

void UShopItemBuyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BuyItemCount)
	{
		BuyItemCount->OnTextChanged.AddDynamic(this, &UShopItemBuyWidget::OnBuyItemCountTextChanged); // 변경이 있을 때
		BuyItemCount->OnTextCommitted.AddDynamic(this, &UShopItemBuyWidget::OnBuyItemCountTextCommitted); // 변경을 확정했을 때(엔터친 후, 포커스를 잃은 후)
	}
	InitShopState();
	Player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	ItemBuyButton->OnClicked.AddDynamic(this, &UShopItemBuyWidget::OnPlayerBuyItem);
}

void UShopItemBuyWidget::SetItemData(UItemDataAsset* InItemData, int32 InStockCount)
{
	InitShopState();

	ItemData = InItemData;
	StockCount = InStockCount;
	//Price = InItemData->ItemPrice;
	BuyItemIcon->SetBrushFromTexture(InItemData->ItemIcon);
	BuyItemName->SetText(InItemData->ItemName);
	BuyItemPrice->SetText(FText::AsNumber(InItemData->ItemPrice));
	BuyItemStockCount->SetText(FText::AsNumber(InStockCount));
	BuyItemDesc->SetText(InItemData->ItemDescription);
}

void UShopItemBuyWidget::InitShopState()
{
	SoldoutPanel->SetVisibility(ESlateVisibility::Hidden);
	BuyItemCount->SetHintText(FText::AsNumber(MinimumBuyItemCount));
	BuyItemCount->SetText(FText::FromString(TEXT("")));
	ItemBuyButton->SetVisibility(ESlateVisibility::Visible);
}

void UShopItemBuyWidget::OnBuyItemCountTextChanged(const FText& Text)
{
	FString number = Text.ToString();
	if (number.IsNumeric())
	{
		int32 count = FCString::Atoi(*number);
		BuyItemCount->SetText(FText::AsNumber(FMath::Clamp(count, MinimumBuyItemCount, StockCount)));
	}
}

void UShopItemBuyWidget::OnBuyItemCountTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	FString number = Text.ToString();
	int32 count = MinimumBuyItemCount;
	if (number.IsNumeric())
	{
		count = FCString::Atoi(*number);
		BuyItemCount->SetText(FText::AsNumber(count));
	}
	else
	{
		BuyItemCount->SetText(FText::AsNumber(count));
	}
	
	//AActionCharacter* player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	if (Player.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("gold : %d"), Player->GetCurrentGold());

		if (Player->GetCurrentGold() < count * ItemData->ItemPrice)
		{
			ItemBuyButton->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if (StockCount > 0) ItemBuyButton->SetVisibility(ESlateVisibility::Visible);
		}
	}
	BuyCount = count;
}

void UShopItemBuyWidget::OnPlayerBuyItem()
{
	
	//APawn* player = GetOwningPlayerPawn();
	if (Player.IsValid())
	{
		if (Player->GetCurrentGold() < BuyCount * ItemData->ItemPrice)
		{
			UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다!"));
		}
		else if (StockCount < BuyCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("재고가 부족합니다!"));
		}
		else
		{
			if (Player->Implements<UInventoryOwner>())
			{
				StockCount -= BuyCount;
				IInventoryOwner::Execute_AddItem(Player.Get(), ItemData, BuyCount);
				IInventoryOwner::Execute_RemoveGold(Player.Get(), BuyCount * ItemData->ItemPrice);
				BuyItemStockCount->SetText(FText::AsNumber(StockCount));
				if (StockCount <= 0)
				{
					
					ShowSoldOut();
				}
			}

		}
	}
}

void UShopItemBuyWidget::ShowSoldOut()
{
	UE_LOG(LogTemp, Log, TEXT("ShowSoldOut"));
	SoldoutPanel->SetVisibility(ESlateVisibility::Visible);
	ItemBuyButton->SetVisibility(ESlateVisibility::Hidden);
}
