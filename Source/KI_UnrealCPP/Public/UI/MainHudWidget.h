// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHudWidget.generated.h"

UENUM(BlueprintType)
enum class EOpenState : uint8
{
	Open	UMETA(DisplayName = "Open"),
	Close	UMETA(DisplayName = "Open")
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

	inline EOpenState GetOpenState() const { return OpenState; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourceBarWidget> HealthBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourceBarWidget> StaminaBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TWeakObjectPtr<class UCooltimeWidget> StaminaCooltimeBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	TObjectPtr<class UInventoryWidget> Inventory = nullptr;

private:
	EOpenState OpenState = EOpenState::Close;
};
