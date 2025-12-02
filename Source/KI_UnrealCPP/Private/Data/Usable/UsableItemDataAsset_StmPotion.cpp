// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Usable/UsableItemDataAsset_StmPotion.h"
#include "Interface/HasStamina.h"

void UUsableItemDataAsset_StmPotion::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UHasStamina>())
	{
		UE_LOG(LogTemp, Log, TEXT("UseItem_Implementation"));
		IHasStamina::Execute_ChargeStamina(InTarget, ChargeAmount);
	}
}
