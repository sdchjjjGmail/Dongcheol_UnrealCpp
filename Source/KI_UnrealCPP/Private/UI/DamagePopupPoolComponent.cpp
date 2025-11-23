// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamagePopupPoolComponent.h"
#include "UI/DamageWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDamagePopupPoolComponent::UDamagePopupPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


UDamageWidget* UDamagePopupPoolComponent::AcquirePopupWidget()
{
	UDamageWidget* Widget = nullptr;

	if (InactivePool.Num() > 0)
	{
		Widget = InactivePool.Pop();
	}
	else
	{
		Widget = CreateNewPopupWidget();
	}

	if (Widget)
	{
		Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
		ActiveWidgets.Add(Widget);
	}

	return Widget;
}

void UDamagePopupPoolComponent::ReleasePopupWidget(UDamageWidget* Widget)
{
	if (!Widget) return;

	Widget->SetVisibility(ESlateVisibility::Collapsed);
	Widget->TargetActor = nullptr;

	ActiveWidgets.Remove(Widget);
	InactivePool.Add(Widget);
}

void UDamagePopupPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < InitialPoolSize; ++i)
	{
		if (UDamageWidget* Widget = CreateNewPopupWidget())
		{
			InactivePool.Add(Widget);
		}
	}
	
}

UDamageWidget* UDamagePopupPoolComponent::CreateNewPopupWidget()
{
	if (!DamagePopupClass) return nullptr;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return nullptr;

	UDamageWidget* Widget = CreateWidget<UDamageWidget>(PC, DamagePopupClass);
	if (Widget)
	{
		Widget->AddToViewport(); // 스크린 공간 HUD로 추가
		Widget->SetVisibility(ESlateVisibility::Collapsed);

		// 애니 끝나면 풀로 반환하도록 델리게이트 바인딩
		Widget->OnPopupFinished.BindUObject(
			this, &UDamagePopupPoolComponent::ReleasePopupWidget);
	}

	return Widget;
}
