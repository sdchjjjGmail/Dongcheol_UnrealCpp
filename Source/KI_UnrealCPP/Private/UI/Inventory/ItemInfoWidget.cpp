// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemInfoWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInfoWidget::SetInfo(UTexture2D* InIcon, FText InName, FText InDesc, int32 InPrice)
{
	ItemIcon->SetBrushFromTexture(InIcon);
	ItemName->SetText(InName);
	ItemDesc->SetText(InDesc);
	ItemPrice->SetText(FText::AsNumber(InPrice));
}

void UItemInfoWidget::ShowDetail(FVector2D Position)
{
	UE_LOG(LogTemp, Log, TEXT("Position : %s"), *Position.ToString());
	SetVisibility(ESlateVisibility::Visible);
	//SetPosition(Position);
}

void UItemInfoWidget::HideDetail()
{
	SetVisibility(ESlateVisibility::Hidden);
}
