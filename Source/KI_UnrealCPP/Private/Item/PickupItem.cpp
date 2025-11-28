// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupItem.h"
#include "Data//ItemDataAsset.h"
#include <Interface/InventoryOwner.h>

void APickupItem::OnPickupComplete_Implementation()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), ItemDatabase, Quantity);
	}
	Super::OnPickupComplete_Implementation();
}
