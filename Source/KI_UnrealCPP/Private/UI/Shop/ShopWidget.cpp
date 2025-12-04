// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopWidget.h"
#include "UI/Shop/ShopItemSellWidget.h"
#include "Player/InventoryComponent.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UShopWidget::InitializeShopWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("샵 위젯 초기화"));

		TargetInventory = InventoryComponent;
	}
	if (ItemSellArea)
	{
		ItemSellArea->SetParentWidget(this);
	}
}

void UShopWidget::PlayOpen()
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UShopWidget::PlayClose()
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
}

void UShopWidget::RequestSellItem(int32 InQuantity, int32 InPrice)
{
	if (TargetInventory.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("아이템을 %d개 팔아 %d골드를 정산합니다."), InQuantity, InPrice * InQuantity / 2);
		TargetInventory->AddGold(InPrice * InQuantity / 2);
	}
}
