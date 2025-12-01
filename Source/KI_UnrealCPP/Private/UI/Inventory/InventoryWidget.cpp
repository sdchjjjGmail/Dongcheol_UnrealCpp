// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "Components/Button.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnInventroyCloseClicked);
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::PlayOpen()
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UInventoryWidget::PlayClose()
{
	if (OpenAndClose) PlayAnimation(OpenAndClose, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
}

void UInventoryWidget::OnInventroyCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();
}
