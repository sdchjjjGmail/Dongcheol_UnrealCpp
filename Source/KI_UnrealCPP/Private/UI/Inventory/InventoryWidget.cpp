// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/GoldPanelWidget.h"
#include "UI/Inventory/ItemInfoWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Player/InventoryComponent.h"
#include <UI/Inventory/IventoryDragDropOperation.h>
#include "Data/ItemDataAsset.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnInventroyCloseClicked);
	}
	SetVisibility(ESlateVisibility::Hidden);
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log, TEXT("인벤토리에 드랍 : 원래 슬롯(%d)으로 아이템이 돌아가야 한다."), invenOp->Index);
		TargetInventory->EditIventorySlot(invenOp->Index, invenOp->Index, invenOp->ItemData.Get(), invenOp->ItemQuantity);
		return true;
	}
	return false;
}

void UInventoryWidget::InitializeInventoryWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent && SlotGridPanel)
	{
		UE_LOG(LogTemp, Log, TEXT("인벤토리 위젯 초기화"));

		TargetInventory = InventoryComponent;
		if (TargetInventory.IsValid())
		{
			if (SlotGridPanel->GetChildrenCount() != TargetInventory->GetInventorySize())
			{
				UE_LOG(LogTemp, Warning, TEXT("인벤토리 컴포넌트와 위젯의 슬롯 크기가 다릅니다"));
				return;
			}

			TargetInventory->OnInventoryGoldChanged.BindUFunction(this, "RefreshGoldWidget");
			TargetInventory->OnInventorySlotChanged.BindUFunction(this, "RefreshSlotWidget");
			RefreshGoldWidget(0);
			int32 size = FMath::Min(SlotGridPanel->GetChildrenCount(), TargetInventory->GetInventorySize());
			for (int i = 0; i < size; i++)
			{
				FInvenSlot* slotData = TargetInventory->GetSlotData(i);
				UInventorySlotWidget* slotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				slotWidget->InitializeSlot(i, slotData);
				slotWidget->OnSlotRightClicked.Clear();
				slotWidget->OnSlotRightClicked.BindUFunction(TargetInventory.Get(), "UseItem");
				slotWidget->SetParentWidget(this);
				SlotWidgets.Add(slotWidget);
			}
		}
	}
}

void UInventoryWidget::RefreshInventoryWidget()
{
	for (const UInventorySlotWidget* slot : SlotWidgets)
	{
		slot->RefreshSlot();
	}
}

void UInventoryWidget::RefreshGoldWidget(int32 InCurrentGold)
{
	InventoryGold->SetGold(InCurrentGold);
}

void UInventoryWidget::RefreshSlotWidget(int32 InIndex)
{
	if (IsValidIndex(InIndex))
	{
		SlotWidgets[InIndex]->RefreshSlot();
	}
}

void UInventoryWidget::ClearInventoryWidget()
{
	TargetInventory = nullptr;
}

void UInventoryWidget::PlayOpen()
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UInventoryWidget::PlayClose()
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
}

void UInventoryWidget::ShowSlotItemDetail(FText InName, FText InDesc, int32 InPrice)
{
	if (InventoryItemDetail)
	{
		InventoryItemDetail->SetInfo(InName, InDesc, InPrice);
		InventoryItemDetail->ShowDetail();
	}
}

void UInventoryWidget::HideSlotItemDetail()
{
	if (InventoryItemDetail) InventoryItemDetail->HideDetail();
}

void UInventoryWidget::RequestIventoryEdit(int32 PrevIndex, int32 InSlotIndex, UItemDataAsset* InItemData, int32 InQuantity)
{
	UE_LOG(LogTemp, Log, TEXT("RequestIventoryEdit %d, %d개"), InSlotIndex, InQuantity);
	if (InQuantity == 0)
	{
		TargetInventory->ClearSlotAtIndex(PrevIndex);
	}
	TargetInventory->EditIventorySlot(PrevIndex, InSlotIndex, InItemData, InQuantity);
}

void UInventoryWidget::RequestThrowItem(UItemDataAsset* InItemData, int32 InIndex, int32 InQuantity)
{
	TargetInventory->ThrowItem(InItemData, InIndex, InQuantity);
}

void UInventoryWidget::OnInventroyCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();
}
