// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/GoldPanelWidget.h"
#include "UI/Inventory/ItemInfoWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Player/InventoryComponent.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnInventroyCloseClicked);
	}
	SetVisibility(ESlateVisibility::Hidden);
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

void UInventoryWidget::OnInventroyCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();
}
