// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GoldDataAsset.h"
#include "Interface/InventoryOwner.h"

void UGoldDataAsset::Execute(AActor* InTarget) const
{
	if (InTarget && InTarget->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddGold(InTarget, Amount);
	}
}
