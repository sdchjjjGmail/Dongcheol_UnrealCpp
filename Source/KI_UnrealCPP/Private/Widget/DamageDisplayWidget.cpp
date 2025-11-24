// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageDisplayWidget.h"
#include "Components/TextBlock.h"

void UDamageDisplayWidget::SetDamageText(float Damage)
{
	if (DamageText)
	{
		DamageText->SetText(FText::AsNumber(static_cast<int32>(Damage)));
	}
}

void UDamageDisplayWidget::PlayPopupAnimation()
{
	if (PopupAnimation)
	{
		PlayAnimation(PopupAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
	}
}
