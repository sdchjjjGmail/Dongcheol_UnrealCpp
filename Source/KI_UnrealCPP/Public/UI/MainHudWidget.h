// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "UI/Shop/ShopWidget.h"
#include "MainHudWidget.generated.h"

UENUM(BlueprintType)
enum class EOpenState : uint8
{
	Open	UMETA(DisplayName = "Open"),
	Close	UMETA(DisplayName = "Close")
};

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UMainHudWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	void OpenInventory();

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	void CloseInventory();

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	void OpenShop();

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	void CloseShop();

	void AddToInventoryCloseDelegate(const FScriptDelegate& Delegate)
	{
		if (Inventory)
		{
			Inventory->OnInventoryCloseRequested.Add(Delegate);
		}
	}

	inline EOpenState GetOpenState() const { return OpenState; }
	inline UInventoryWidget* GetInventoryWidget() const { return Inventory; }
	inline UShopWidget* GetShopWidget() const { return Shop; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourceBarWidget> HealthBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourceBarWidget> StaminaBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TWeakObjectPtr<class UCooltimeWidget> StaminaCooltimeBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	TObjectPtr<UInventoryWidget> Inventory = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop", meta = (BindWidget))
	TObjectPtr<UShopWidget> Shop = nullptr;

private:
	EOpenState OpenState = EOpenState::Close;
};
