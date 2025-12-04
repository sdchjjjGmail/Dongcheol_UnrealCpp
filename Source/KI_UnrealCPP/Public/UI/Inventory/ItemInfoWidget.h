// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void ShowDetail(UTexture2D* InIcon, FText InName, FText InDesc, int32 InPrice);
	void HideDetail();
	inline void SetParentPosition(const FVector2D& InPosition) { ParentPosition = InPosition; }

private:
	void SetInfo(UTexture2D* InIcon, FText InName, FText InDesc, int32 InPrice);
	void UpdateLocation();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UImage> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemName = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemDesc = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemPrice = nullptr;

private:
	UPROPERTY()
	APlayerController* PlayerController = nullptr;
	
	UPROPERTY()
	UCanvasPanelSlot* CanvasSlot = nullptr;

	FVector2D ParentPosition;
};
