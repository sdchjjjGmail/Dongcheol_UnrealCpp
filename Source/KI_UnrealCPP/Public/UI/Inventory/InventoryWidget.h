// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryCloseRequested);

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	void InitializeInventoryWidget(class UInventoryComponent* InventoryComponent);
	void RefreshInventoryWidget();

	UFUNCTION()
	void RefreshGoldWidget(int32 InCurrentGold);
	
	UFUNCTION()
	void RefreshSlotWidget(int32 InIndex);
	
	void ClearInventoryWidget();

	UFUNCTION()
	void PlayOpen();

	UFUNCTION()
	void PlayClose();

	UFUNCTION()
	void ShowSlotItemDetail(FText InName, FText InDesc, int32 InPrice);

	UFUNCTION()
	void HideSlotItemDetail();

	void RequestIventoryEdit(int32 PrevIndex, int32 InSlotIndex, class UItemDataAsset* InItemData, int32 InQuantity);

public:
	UPROPERTY(BlueprintAssignable, Category = "UI|Inventory")
	FOnInventoryCloseRequested OnInventoryCloseRequested;

private:
	UFUNCTION()
	void OnInventroyCloseClicked();

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	inline bool IsValidIndex(int32 InSlotIndex) const {
		return InSlotIndex < SlotWidgets.Num() && InSlotIndex >= 0;
	}

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OpenAndClose = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> SlotGridPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UGoldPanelWidget> InventoryGold = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UItemInfoWidget> InventoryItemDetail = nullptr;

	//UPROPERTY(Transient, meta = (BindWidgetAnim))
	//TObjectPtr<UWidgetAnimation> Close = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;

	TArray <TObjectPtr<class UInventorySlotWidget>> SlotWidgets;
};
