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

public:
	UFUNCTION()
	void PlayOpen();

	UFUNCTION()
	void PlayClose();

public:
	UPROPERTY(BlueprintAssignable, Category = "UI|Inventory")
	FOnInventoryCloseRequested OnInventoryCloseRequested;
	
private:
	UFUNCTION()
	void OnInventroyCloseClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OpenAndClose = nullptr;

	//UPROPERTY(Transient, meta = (BindWidgetAnim))
	//TObjectPtr<UWidgetAnimation> Close = nullptr;
};
