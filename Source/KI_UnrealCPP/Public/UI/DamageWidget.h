// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnPopupFinished, UDamageWidget*);

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // 데미지 텍스트 셋팅
    UFUNCTION(BlueprintCallable, Category = "DamagePopup")
    void SetDamageValue(int32 InDamage);

    // 팝업 시작 (애니메이션 재생)
    UFUNCTION(BlueprintCallable, Category = "DamagePopup")
    void PlayPopup();

    // 이 위젯이 어느 적을 기준으로 뜨는지 (위치 계산용)
    UPROPERTY(BlueprintReadWrite, Category = "DamagePopup")
    TWeakObjectPtr<AActor> TargetActor;


    FOnPopupFinished OnPopupFinished;

protected:
    // BP에서 만든 TextBlock 바인딩
    UPROPERTY(meta = (BindWidget))
    TWeakObjectPtr<class UTextBlock> DamageText;

    // BP에서 만든 Animation 바인딩
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TWeakObjectPtr<class UWidgetAnimation> PopupAnim;

    virtual void NativeConstruct() override;

    UFUNCTION()
    void HandleAnimationFinished();
	
};
