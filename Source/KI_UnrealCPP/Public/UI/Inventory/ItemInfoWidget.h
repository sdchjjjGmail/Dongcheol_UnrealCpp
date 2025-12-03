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

	//void SetInfo( FText InName, FText InDesc, int32 InPrice);

public:
	void SetInfo(UTexture2D* InIcon, FText InName, FText InDesc, int32 InPrice);

	void ShowDetail(FVector2D Position);
	void HideDetail();
	
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

};
