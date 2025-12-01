// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
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

			int32 size = FMath::Min(SlotGridPanel->GetChildrenCount(), TargetInventory->GetInventorySize());
			for (int i = 0; i < size; i++)
			{
				FInvenSlot* slotData = TargetInventory->GetSlotData(i);
				UInventorySlotWidget* slotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				slotWidget->InitializeSlot(i, slotData);
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

void UInventoryWidget::OnInventroyCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();
}
