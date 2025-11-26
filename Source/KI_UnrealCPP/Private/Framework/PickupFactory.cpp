// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PickupFactory.h"
#include "Settings/PickupSettings.h"
#include "Data/DataTableRows.h"

void UPickupFactory::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UPickupFactory : 초기화 시작"));

	LoadPickupClassesMap();
}

APickupActor* UPickupFactory::SpawnPickup(
	EItemCode InCode,
	FVector InLocation,
	FRotator InRotator,
	FVector Velocity)
{
	APickupActor* spawnedPickup = nullptr;
	if (PickupClasses.Contains(InCode))
	{
		UWorld* world = GetWorld();
		spawnedPickup = world->SpawnActor<APickupActor>(PickupClasses[InCode], InLocation, InRotator);
		spawnedPickup->AddImpulse(Velocity);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPickupFactory : 설정되지 않은 아이템을 생성하려고 합니다."));
	}
	return spawnedPickup;
}

void UPickupFactory::LoadPickupClassesMap()
{
	const UPickupSettings* settings = GetDefault<UPickupSettings>();

	if (settings && !settings->PickupDataTable.IsNull())
	{
		UDataTable* dataTable = settings->PickupDataTable.LoadSynchronous();
		if (dataTable)
		{
			TArray<FPickupData_TableRow*> allRows;
			dataTable->GetAllRows(TEXT(""), allRows);
			for (const FPickupData_TableRow* row : allRows)
			{
				if (PickupClasses.Contains(row->PickupCode))
				{
					UE_LOG(LogTemp, Warning, TEXT("UPickupFactory : 키 값이 중복입니다. 이전 값은 덮어써집니다."));
				}
				PickupClasses.Add(row->PickupCode, row->PickupClass);
			}
			UE_LOG(LogTemp, Log, TEXT("UPickupFactory : 로딩 완료"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UPickupFactory : DataTable 로딩 실패"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPickupFactory : PickupDataTable is null"));
	}
}
