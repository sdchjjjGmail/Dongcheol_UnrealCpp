// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemInfoWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CanvasSlot = Cast<UCanvasPanelSlot>(Slot);

	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInfoWidget::ShowDetail(UTexture2D* InIcon, FText InName, FText InDesc, int32 InPrice)
{
	SetInfo(InIcon, InName, InDesc, InPrice);
	UpdateLocation();
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UItemInfoWidget::HideDetail()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateLocation();
}

void UItemInfoWidget::SetInfo(UTexture2D* InIcon, FText InName, FText InDesc, int32 InPrice)
{
	ItemIcon->SetBrushFromTexture(InIcon);
	ItemName->SetText(InName);
	ItemDesc->SetText(InDesc);
	ItemPrice->SetText(FText::AsNumber(InPrice));
}

void UItemInfoWidget::UpdateLocation()
{
	if (!PlayerController)
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
	}
	
	FVector2D mousePosition;
	
	mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	CanvasSlot->SetPosition(mousePosition - ParentPosition);

	//if (UWidgetLayoutLibrary::GetMousePositionScaledByDPI(PlayerController, mousePosition.X, mousePosition.Y))
	//{
		UE_LOG(LogTemp, Log, TEXT("mouse location : %s"), *mousePosition.ToString());
	//}
}
