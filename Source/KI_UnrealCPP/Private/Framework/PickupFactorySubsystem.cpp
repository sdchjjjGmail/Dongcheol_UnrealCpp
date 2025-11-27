// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PickupFactorySubsystem.h"
#include "Settings/DropItemSettings.h"
#include "Data/DataTableRows.h"
#include "Item/PickupActor.h"
#include <Weapon/UsedWeapon.h>

void UPickupFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPickupFactorySubsystem::DropEnemyItem(
	UDataTable* DropItemTable,
	FVector DropLocation, FRotator DropRtation)
{
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("invalid GetWorld"));
		return;
	}

	if (DropItemTable)
	{
		APickupActor* pickup = nullptr;
		TMap<FName, uint8*> RowMap = DropItemTable->GetRowMap();
		if (RowMap.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("invalid RowMap"));
			return;
		}

		// 중복으로 당첨 가능
		for (const auto& element : RowMap)
		{
			FDropItemData_v1_TableRow* row = (FDropItemData_v1_TableRow*)element.Value;
			if (row && row->DropRate && row->DropItemClass)
			{
				if (FMath::FRand() <= row->DropRate)
				{
					GetWorld()->SpawnActor<APickupActor>(
						row->DropItemClass,
						DropLocation + FVector::UpVector * 100.0f,
						DropRtation
					);
				}
			}
		}
	}
}

void UPickupFactorySubsystem::DropValidWeapon(
	TSubclassOf<APickupActor> PickupClass, 
	int32 RemainingUseCount, 
	FVector DropLocation,
	FRotator DropRtation,
	FVector velocity)
{
	//APickupActor* pickup = GetWorld()->SpawnActor<APickupActor>(
	//	PickupClass,
	//	DropLocation,
	//	DropRtation);

	//// 새로 생긴 픽업에 남은 횟수 넣기
	//pickup->SetPickupCount(RemainingUseCount);

	//pickup->AddImpulse(velocity);
}

