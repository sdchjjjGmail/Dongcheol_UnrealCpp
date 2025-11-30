// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/InventoryComponent.h"
#include "UI/ItemTooltipWidget.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // 인벤토리 + 슬롯 인덱스로 초기화
    void InitSlot(UInventoryComponent* InInventory, int32 InSlotIndex);

    // 인벤토리 변경 시 다시 그려줄 함수
    void Refresh();

    int32 GetSlotIndex() const { return SlotIndex; }

protected:
    UPROPERTY(meta = (BindWidget))
    class UImage* ItemIcon;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CountText;

    UPROPERTY(EditAnywhere, Category = "Inventory")
    TSubclassOf<UItemTooltipWidget> TooltipWidgetClass;

    virtual void NativeOnInitialized() override;
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

    UPROPERTY()
    UInventoryComponent* Inventory;

    int32 SlotIndex = -1;

    UPROPERTY()
    UItemTooltipWidget* TooltipWidget;
};
