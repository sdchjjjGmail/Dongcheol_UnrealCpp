// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHudWidget.h"
#include "Player/ActionCharacter.h"
#include "Player/ResourceComponent.h"
#include "UI/ResourceBarWidget.h"
#include "UI/CooltimeWidget.h"

void UMainHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseInventory();
	AActionCharacter* player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	if (player)
	{
		if (player->GetResourceComponent())
		{
			UResourceComponent* resource = player->GetResourceComponent();
			resource->OnHealthChanged.AddUObject(HealthBar.Get(), &UResourceBarWidget::RefreshWidget);
			resource->OnStaminaChanged.AddDynamic(StaminaBar.Get(), &UResourceBarWidget::RefreshWidget);
			resource->OnStaminaEmpty.AddDynamic(StaminaCooltimeBar.Get(), &UCooltimeWidget::SetCooltime);

			HealthBar->RefreshWidget(resource->GetCurrentHealth(), resource->GetMaxHealth());
			StaminaBar->RefreshWidget(resource->GetCurrentStamina(), resource->GetMaxStamina());
		}
		if (UInventoryComponent* inventoryComponent = player->GetInventoryComponent())
		{
			//Inventory->OnInventoryCloseRequested.AddDynamic(this, &UMainHudWidget::CloseInventory);
			
			// inventoryComponent의 내용을 바탕으로 InventoryWidget을 채우기
		}
	}
}

void UMainHudWidget::OpenInventory()
{
	Inventory->RefreshInventoryWidget();
	Inventory->SetVisibility(ESlateVisibility::Visible);
	OpenState = EOpenState::Open;
	Inventory->PlayOpen();
}

void UMainHudWidget::CloseInventory()
{
	Inventory->PlayClose();
	OpenState = EOpenState::Close;
	//Inventory->SetVisibility(ESlateVisibility::Hidden);
}
