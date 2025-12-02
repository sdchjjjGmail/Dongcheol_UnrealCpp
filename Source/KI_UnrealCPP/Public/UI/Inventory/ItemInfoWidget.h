// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public:
	void SetInfo(FText InName, FText InDesc, int32 InPrice);

	void ShowDetail();
	void HideDetail();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemName = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemDesc = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI|InventoryItemInfo", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemPrice = nullptr;

private:

};
