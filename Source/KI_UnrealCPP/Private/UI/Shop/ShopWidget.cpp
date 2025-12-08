// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopWidget.h"
#include "UI/Shop/ShopItemSellWidget.h"
#include "UI/Shop/ShopItemListWidget.h"
#include "Player/InventoryComponent.h"
#include "Components/Button.h"
#include "UI/MainHudWidget.h"
#include <Player/ActionPlayerController.h>
#include <Interface/InventoryOwner.h>

void UShopWidget::InitializeShopWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent)
	{
		//UE_LOG(LogTemp, Log, TEXT("샵 위젯 초기화"));

		TargetInventory = InventoryComponent;
	}
	if (ItemSellArea)
	{
		ItemSellArea->SetParentWidget(this);
	}
	if (ExitShop.IsValid())
	{
		ExitShop->OnClicked.AddDynamic(this, &UShopWidget::OnExitButtonClicked);
	}
}

void UShopWidget::PlayOpen(UDataTable* InTable)
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
	ResetShopItemListWidget(InTable);
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
		//TargetInventory->AddGold(InPrice * InQuantity / 2);
		APawn* player = GetOwningPlayerPawn();
		if (player->Implements<UInventoryOwner>())
		{
			// 판매액만큼 돈을 추가
			IInventoryOwner::Execute_AddGold(player, InPrice * InQuantity / 2);
		}
	}
}

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UShopWidget::ResetShopItemListWidget(UDataTable* InTable)
{
	//UE_LOG(LogTemp, Log, TEXT("ResetShopItemListWidget"));
	ShopItemList = InTable;
	if (ShopItemList.IsValid())
	{
		ItemListWidget->ResetItemList(InTable);
	}
}

void UShopWidget::OnExitButtonClicked()
{
	//UE_LOG(LogTemp, Log, TEXT("OnExitButtonClicked"));
	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwningPlayer());
	if (playerController) playerController->CloseShopWidget();
}
