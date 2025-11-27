// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/HealthOrbDataAsset.h"
#include <Interface/HasHealth.h>

void UHealthOrbDataAsset::Execute(AActor* InTarget) const
{
	if (InTarget && InTarget->Implements<UHasHealth>())
	{
		IHasHealth::Execute_HealHealth(InTarget, HealAmount);
	}
}
