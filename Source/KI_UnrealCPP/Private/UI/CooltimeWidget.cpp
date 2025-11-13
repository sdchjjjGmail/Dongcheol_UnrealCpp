// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CooltimeWidget.h"
#include "Components/ProgressBar.h"
#include "Player/ResourceComponent.h"

void UCooltimeWidget::SetCooltime()
{
	CurrentCooltime = 0;
	GetWorld()->GetTimerManager().SetTimer(
		Cooltimer,
		[this]() {
			StaminaCooltime->SetPercent(CurrentCooltime / Cooltime);
			CurrentCooltime += CooltimeTick;
			if (CurrentCooltime >= Cooltime)
			{
				GetWorld()->GetTimerManager().ClearTimer(Cooltimer);
			}
		},
		CooltimeTick,
		true
	);
}
