// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHudWidget.h"
#include "Player/ActionCharacter.h"
#include "Player/ResourceComponent.h"
#include "UI/ResourceBarWidget.h"
#include "UI/CooltimeWidget.h"

void UMainHudWidget::NativeConstruct()
{
	AActionCharacter* player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	if (player && player->GetResourceComponent())
	{
		UResourceComponent* resource = player->GetResourceComponent();
		resource->OnHealthChanged.AddUObject(HealthBar.Get(), &UResourceBarWidget::RefreshWidget);
		resource->OnStaminaChanged.AddDynamic(StaminaBar.Get(), &UResourceBarWidget::RefreshWidget);
		resource->OnStaminaEmpty.AddDynamic(StaminaCooltimeBar.Get(), &UCooltimeWidget::SetCooltime);

		HealthBar->RefreshWidget(resource->GetCurrentHealth(), resource->GetMaxHealth());
		StaminaBar->RefreshWidget(resource->GetCurrentStamina(), resource->GetMaxStamina());
	}
}
