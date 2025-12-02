// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Usable/UsableItemDataAsset_HealthPotion.h"
#include "Interface/HasHealth.h"

void UUsableItemDataAsset_HealthPotion::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UHasHealth>())
	{
		UE_LOG(LogTemp, Log, TEXT("UseItem_Implementation"));
		IHasHealth::Execute_HealHealth(InTarget, HealAmount);
	}
}
