// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupWeapon.h"
#include "Interface/InventoryOwner.h"

void APickupWeapon::OnPickupComplete_Implementation()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddWeapon(PickupOwner.Get(), PickupWeapon, UseCount);
	}

	Super::OnPickupComplete_Implementation();
}
