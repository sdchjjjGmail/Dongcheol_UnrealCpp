// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UDamageDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetDamageText(float Damage);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayPopupAnimation();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DamageText = nullptr;
	
	// Transient : 런타임에 임시로 생성한다고 명시, BindWidgetAnim : 애니메이션 바인딩
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> PopupAnimation = nullptr;
};
