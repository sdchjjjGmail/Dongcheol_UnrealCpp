// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Usable/UsableItemDataAsset_Gem.h"
#include <Interface/InventoryOwner.h>

void UUsableItemDataAsset_Gem::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UInventoryOwner>())
	{
		UE_LOG(LogTemp, Log, TEXT("Execute_AddGold"));
		int32 gold = FMath::RandRange(MinGold, MaxGold);
		IInventoryOwner::Execute_AddGold(InTarget, gold);
	}
}
