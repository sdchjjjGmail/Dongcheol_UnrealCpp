// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CooltimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UCooltimeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCooltime();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	TObjectPtr<class UResourceComponent> Resource = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TWeakObjectPtr<class UProgressBar> StaminaCooltime;

private:
	FTimerHandle Cooltimer;
	float CurrentCooltime = 0.0f;
	float Cooltime = 3.0f;
	float CooltimeTick = 0.1f;
};
