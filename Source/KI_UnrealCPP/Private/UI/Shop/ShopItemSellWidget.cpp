// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemSellWidget.h"
#include <UI/Inventory/IventoryDragDropOperation.h>
#include "UI/Shop/ShopWidget.h"

void UShopItemSellWidget::InitSellArea()
{
}

bool UShopItemSellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log, TEXT("판매 드랍 : 슬롯 (%d) 아이템을 팝니다."), invenOp->Index);
		if (ParentWidget.IsValid())
		{
			ParentWidget->RequestSellItem(invenOp->ItemQuantity, invenOp->Price);
		}

		return true;
	}
	return false;
}

