// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemTooltipWidget.h"
#include "Components/TextBlock.h"

void UItemTooltipWidget::SetItemData(UItemDataAsset* InItemData, int32 InCount)
{
    if (!InItemData)
    {
        if (NameText)        NameText->SetText(FText::GetEmpty());
        if (DescriptionText) DescriptionText->SetText(FText::GetEmpty());
        if (PriceText)       PriceText->SetText(FText::GetEmpty());
        if (CountText)       CountText->SetText(FText::GetEmpty());
        return;
    }

    if (NameText)
    {
        NameText->SetText(InItemData->ItemName);
    }

    if (DescriptionText)
    {
        DescriptionText->SetText(InItemData->ItemDescription);
    }

    if (PriceText)
    {
        FText PriceFmt = FText::Format(FText::FromString(TEXT("{0} G")), FText::AsNumber(InItemData->ItemPrice));
        PriceText->SetText(PriceFmt);
    }

    if (CountText)
    {
        CountText->SetText(FText::AsNumber(InCount));
    }
}
