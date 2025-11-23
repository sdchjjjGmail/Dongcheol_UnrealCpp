// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UDamageWidget::SetDamageValue(int32 InDamage)
{
    if (DamageText.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("DamageText : %d"), InDamage);
        DamageText->SetText(FText::AsNumber(InDamage));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("invlid DamageText"));
    }
}

void UDamageWidget::PlayPopup()
{
    if (PopupAnim.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayAnimation"));
        PlayAnimation(PopupAnim.Get());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("invlid PopupAnim"));
    }
}

void UDamageWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 애니메이션 끝났을 때 콜백
    if (PopupAnim.IsValid())
    {
        FWidgetAnimationDynamicEvent FinishedEvent;
        FinishedEvent.BindDynamic(this, &UDamageWidget::HandleAnimationFinished);

        BindToAnimationFinished(PopupAnim.Get(), FinishedEvent);
    }
}

void UDamageWidget::HandleAnimationFinished()
{
    // 풀로 반환 요청
    if (OnPopupFinished.IsBound())
    {
        OnPopupFinished.Execute(this);
    }
    else
    {
        // 풀 없으면 그냥 숨기기
        SetVisibility(ESlateVisibility::Collapsed);
    }
}
