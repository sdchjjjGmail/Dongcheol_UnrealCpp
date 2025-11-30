// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/InventoryComponent.h"
#include "Data/ItemDataAsset.h"
#include "UI/ItemTooltipWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventorySlotWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    if (!Inventory || !Inventory->IsValidIndex(SlotIndex)) return;

    const FInvenSlot& Slot = Inventory->GetSlotData(SlotIndex);
    if (Slot.IsEmpty() || !TooltipWidgetClass) return;

    if (!TooltipWidget)
    {
        TooltipWidget = CreateWidget<UItemTooltipWidget>(GetWorld(), TooltipWidgetClass);
    }

    if (TooltipWidget)
    {
        TooltipWidget->SetItemData(Slot.ItemData, Slot.GetCount());
        UWidgetBlueprintLibrary::SetHardwareCursor(this, EMouseCursor::Default, NAME_None, FVector2D::ZeroVector);
        SetToolTip(TooltipWidget);
    }
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    SetToolTip(nullptr);
}

void UInventorySlotWidget::InitSlot(UInventoryComponent* InInventory, int32 InSlotIndex)
{
    Inventory = InInventory;
    SlotIndex = InSlotIndex;

    Refresh();
}

void UInventorySlotWidget::Refresh()
{
    if (!Inventory || !Inventory->IsValidIndex(SlotIndex))
    {
        if (ItemIcon)  ItemIcon->SetBrushFromTexture(nullptr);
        if (CountText)
        {
            CountText->SetText(FText::GetEmpty());
            CountText->SetVisibility(ESlateVisibility::Collapsed);
        }
        return;
    }

    const FInvenSlot& Slot = Inventory->GetSlotData(SlotIndex);

    if (Slot.IsEmpty())
    {
        if (ItemIcon)  ItemIcon->SetBrushFromTexture(nullptr);
        if (CountText)
        {
            CountText->SetText(FText::GetEmpty());
            CountText->SetVisibility(ESlateVisibility::Collapsed);
        }
        return;
    }

    // 🔹 여기서 DataAsset 사용
    if (ItemIcon)
    {
        ItemIcon->SetBrushFromTexture(Slot.ItemData->ItemIcon);
    }

    if (CountText)
    {
        const int32 Count = Slot.GetCount();
        if (Count > 1)
        {
            CountText->SetText(FText::AsNumber(Count));
            CountText->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
        else
        {
            CountText->SetText(FText::GetEmpty());
            CountText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}
