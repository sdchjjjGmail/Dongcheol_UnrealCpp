// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupHealthOrb.h"
#include "Interface/HasHealth.h"

void APickupHealthOrb::OnConsume()
{
	Super::OnConsume();

	if (PickupOwner.IsValid() && PickupOwner->Implements<UHasHealth>())
	{
		IHasHealth::Execute_HealHealth(PickupOwner.Get(), HealAmount);
	}
}
