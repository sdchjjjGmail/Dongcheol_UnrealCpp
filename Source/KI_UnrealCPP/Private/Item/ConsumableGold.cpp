// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumableGold.h"
#include <Interface/InventoryOwner.h>

//void AConsumableGold::OnPickupComplete_Implementation()
//{
	//PickupItem = PickupItemGold;
	//Quantity = Amount;
//	Super::OnPickupComplete_Implementation(); // 자기 자신을 삭제시키기 때문에 마지막에 처리
//}

void AConsumableGold::OnConsume()
{
	Super::OnConsume();

	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddGold(PickupOwner.Get(), Gold);
	}
}
