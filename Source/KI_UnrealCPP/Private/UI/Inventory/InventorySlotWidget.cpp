// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/ItemInfoWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/IventoryDragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/InventoryComponent.h"

void UInventorySlotWidget::InitializeSlot(int32 InIndex, FInvenSlot* InSlotData)
{
	Index = InIndex;
	SlotData = InSlotData;

	RefreshSlot();
}

void UInventorySlotWidget::RefreshSlot() const
{
	UE_LOG(LogTemp, Log, TEXT("RefreshSlot"));
	if (SlotData && !SlotData->IsEmpty())
	{
		// 슬롯에 아이템이 들어있으면 들어있는 아이템 보여주기
		ItemIconImage->SetBrushFromTexture(SlotData->ItemData->ItemIcon);
		ItemIconImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

		CountText->SetText(FText::AsNumber(SlotData->GetCount()));
		MaxCountText->SetText(FText::AsNumber(SlotData->ItemData->ItemMaxStackCount));

		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SeparateText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		MaxCountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		// 슬롯에 아이템이 없으면 슬롯 클리어
		ClearSlotWidget();
	}
}

void UInventorySlotWidget::ClearSlotWidget() const
{
	ItemIconImage->SetBrushFromTexture(nullptr);
	ItemIconImage->SetBrushTintColor(FLinearColor::Transparent);
	
	CountText->SetVisibility(ESlateVisibility::Hidden);
	SeparateText->SetVisibility(ESlateVisibility::Hidden);
	MaxCountText->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UE_LOG(LogTemp, Log, TEXT("DragDetected : %d Slot"), this->Index);
	if (SlotData->ItemData)
	{
		UIventoryDragDropOperation* DragOp = NewObject<UIventoryDragDropOperation>();
		DragOp->Index = this->Index;
		DragOp->ItemData = SlotData->ItemData;
		DragOp->ItemQuantity = SlotData->GetCount();

		if (DragVisualClass)
		{
			UInventorySlotWidget* DragVisual = CreateWidget<UInventorySlotWidget>(GetWorld(), DragVisualClass);
			if (DragVisual)
			{
				// ex) DragVisual 내부에 아이템 아이콘, 수량 텍스트 등 세팅하고 싶으면
				UInventorySlotWidget* TypedVisual = Cast<UInventorySlotWidget>(DragVisual);
				 if (TypedVisual) { TypedVisual->InitializeSlot(DragOp->Index, SlotData); }
				 
				DragOp->DefaultDragVisual = DragVisual;
				DragOp->Pivot = EDragPivot::MouseDown;  // 클릭한 지점 기준으로 따라다니게
			}
		}

		ParentWidget->RequestIventoryEdit(Index, Index, SlotData->ItemData.Get(), 0);
		OutOperation = DragOp;
	}
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log, TEXT("Drop : %d Slot에 %s를 옮기기"),
			Index,
			*(invenOp->ItemData->ItemName.ToString()));
		ParentWidget->RequestIventoryEdit(invenOp->Index, Index, invenOp->ItemData.Get(), invenOp->ItemQuantity);
		return true;
	}
	return false;
}

void UInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log,
			TEXT("DragCancelled : 바닥에다가 (%s)아이템을 버려야 한다."),
			*(invenOp->ItemData->ItemName.ToString()));
		ParentWidget->RequestThrowItem(invenOp->ItemData.Get(), invenOp->Index, invenOp->ItemQuantity);
	}
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (ParentWidget && SlotData->ItemData)
		ParentWidget->ShowSlotItemDetail(
			SlotData->ItemData->ItemName,
			SlotData->ItemData->ItemDescription,
			SlotData->ItemData->ItemPrice);
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (ParentWidget)
		ParentWidget->HideSlotItemDetail();
	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)) // 마우스 오른쪽 버튼 눌렸는지 확인
	{
		if (SlotData->ItemData)
		{
			UE_LOG(LogTemp, Log, TEXT("%d Slot : Right Click(%s)"),
				Index, *SlotData->ItemData->ItemName.ToString());
			OnSlotRightClicked.ExecuteIfBound(Index);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%d Slot : Right Click(empty)"), Index);
		}
		return FReply::Handled(); // 이 마우스 클릭은 완료되었다 라고 전달
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) // 마우스 왼쪽 버튼 눌렸는지 확인
	{

		return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent); // 나는 처리 안했다 or 부모 or 다른 위젯이 처리
}
