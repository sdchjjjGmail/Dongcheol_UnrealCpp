// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupConsumable.h"
#include "Interface/Pickupable.h"
#include <Interface/InventoryOwner.h>

void APickupConsumable::OnPickupComplete_Implementation()
{
	OnConsume();
	//UE_LOG(LogTemp, Log, TEXT("APickupConsumable::OnPickupComplete_Implementation()"));
	//if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	//{
	//	IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem, Quantity);
	//}

	Super::OnPickupComplete_Implementation(); // 자기 자신을 삭제시키기 때문에 마지막에 처리
}

void APickupConsumable::OnConsume()
{
	if (DataAsset)
	{
		DataAsset->Execute(PickupOwner.Get());
	}
}