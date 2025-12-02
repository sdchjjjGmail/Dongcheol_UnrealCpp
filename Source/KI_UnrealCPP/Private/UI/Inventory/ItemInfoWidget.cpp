// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemInfoWidget.h"
#include "Components/TextBlock.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInfoWidget::SetInfo(FText InName, FText InDesc, int32 InPrice)
{
	ItemName->SetText(InName);
	ItemDesc->SetText(InDesc);
	ItemPrice->SetText(FText::AsNumber(InPrice));
}

void UItemInfoWidget::ShowDetail()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UItemInfoWidget::HideDetail()
{
	SetVisibility(ESlateVisibility::Hidden);
}
