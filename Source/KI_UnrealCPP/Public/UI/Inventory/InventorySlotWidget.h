// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

struct FInvenSlot;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSlotClicked, int32, InSlotIndex);
/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 이 위젯이 보여줄 데이터를 세팅
	void InitializeSlot(int32 InIndex, FInvenSlot* InSlotData);

	// 설정된 데이터를 기반으로 위젯에서 표시하는 내용을 갱신
	void RefreshSlot() const;

	void SetParentWidget(class UInventoryWidget* InWidget) { ParentWidget = InWidget; }

protected:
	void ClearSlotWidget() const;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	FOnSlotClicked OnSlotRightClicked;

protected:
	UPROPERTY(VisibleAnywhere, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> CountText = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> SeparateText = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxCountText = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventorySlot")
	TObjectPtr<class UInventoryWidget> ParentWidget = nullptr;

private:
	int32 Index = -1;

	//UPROPERTY()
	FInvenSlot* SlotData = nullptr;
};
