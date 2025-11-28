// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupItem.h"
#include <Interface/InventoryOwner.h>

void APickupItem::OnPickupComplete_Implementation()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem, Quantity);
	}
	Super::OnPickupComplete_Implementation();
}
