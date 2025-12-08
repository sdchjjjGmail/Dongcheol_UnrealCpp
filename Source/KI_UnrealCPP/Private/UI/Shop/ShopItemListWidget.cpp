// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemListWidget.h"
#include "UI/Shop/ShopItemBuyWidget.h"
#include "Data/DataTableRows.h"
#include "Components/VerticalBox.h"

void UShopItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemBuyContainer)
	{
		int32 count = ItemBuyContainer->GetChildrenCount();
		ShopItems.Empty(count);
		for (int32 i = 0; i < count; i++)
		{
			UShopItemBuyWidget* itemWidget = Cast<UShopItemBuyWidget>(ItemBuyContainer->GetChildAt(i));
			ShopItems.Add(itemWidget);
		}
	}
}

void UShopItemListWidget::ResetItemList(UDataTable* ItemList)
{
	int32 index = 0;
	int32 selectIndex = 0;
	float totlaWeight = 0.0f;

	TArray<FShopData_TableRow*> allRows;
	ItemList->GetAllRows(TEXT("ShopDataTable"), allRows);
	for (FShopData_TableRow* row : allRows)
	{
		totlaWeight += row->SelectWeight;
	}

	int32 selectcCount = ShopItems.Num();
	TArray<FShopData_TableRow*> selectedRows;
	selectedRows.Empty(selectcCount);
	for (int32 i = 0; i < ShopItems.Num(); i++)
	{
		float hit = FMath::FRandRange(0.0f, totlaWeight);
		float currentWeight = 0.0f;
		for (FShopData_TableRow* row : allRows)
		{
			currentWeight += row->SelectWeight;
			if (hit < currentWeight)
			{
				//selectedRows.Add(row);
				ShopItems[selectIndex]->SetItemData(row->ItemData, row->StockCount);
				selectIndex++;
				break;
			}
		}
	}

	//for (int32 i = 0; i < selectcCount; i++)
	//{
	//	const FShopData_TableRow* row = selectedRows[i];
	//	ShopItems[i]->SetItemData(row->ItemData, row->StockCount);
	//}
}
