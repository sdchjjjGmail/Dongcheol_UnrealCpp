// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WeaponManagerComponent.h"
#include "Player/ActionCharacter.h"
#include "Weapon/WeaponActor.h"
#include "Weapon/UsedWeapon.h"
#include "Item/PickupActor.h"
#include "Interface/Consumable.h"

// Sets default values for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


TSubclassOf<AUsedWeapon> UWeaponManagerComponent::GetUsedWeaponClass(EItemCode InType) const
{
	const UWeaponDataAsset* dataAsset = *WeaponDatabase.Find(InType);
    return dataAsset->UsedWeaponClass;
}

// Called when the game starts
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<AActionCharacter>(GetOwner());

	ValidateWeaponDatabase();
	SpawnWeaponInstances();

	OwnerPlayer->EquipWeapon(EItemCode::Saw);
}

void UWeaponManagerComponent::ValidateWeaponDatabase()
{
	if (WeaponDatabase.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("무기 데이터베이스가 비었음!"));
	}
	else
	{
		for (const auto& pair : WeaponDatabase)
		{
			if (!pair.Value)
			{
				UE_LOG(LogTemp, Error, TEXT("무기(%d)의 데이터가 null"),
					static_cast<int32>(pair.Key));
			}
			else if (!pair.Value->IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("무기(%d)의 데이터가 유효하지 않습니다."),
					static_cast<int32>(pair.Key));
			}
			else if (pair.Key != pair.Value->WeaponType)
			{
				UE_LOG(LogTemp, Warning, TEXT("무기(%d)의 키 값과 데이터 타입이 서로 다릅니다."),
					static_cast<int32>(pair.Key));
			}
		}
	}
}

void UWeaponManagerComponent::SpawnWeaponInstances()
{
	WeaponInstances.Empty(WeaponDatabase.Num()); // WeaponInstances의 할당 크기를 필요한 만큼만 설정
	
	if(OwnerPlayer.IsValid())
	{
		UWorld* world = GetWorld();
		FVector defaultLocation = FVector(0.0f, 0.0f, -10000.0f);
		for (const auto& pair : WeaponDatabase)
		{
			AWeaponActor* weapon = world->SpawnActor<AWeaponActor>(
				pair.Value->EquippedWeaponClass,
				defaultLocation,
				FRotator::ZeroRotator // 일단 defaultLocation위치에 생성
			);
			weapon->AttachToComponent(
				OwnerPlayer->GetMesh(),
				FAttachmentTransformRules::KeepWorldTransform,
				FName("root") // 월드 아웃라이너에서 확인하기 위해 플레이어 아래에 붙음
			);
			weapon->SetWeaponOwner(OwnerPlayer.Get()); // 무기의 오너 설정
			weapon->WeaponActivate(false); // 무기 비활성화

			
			//if (IConsumable* consumableWeapon = Cast<IConsumable>(weapon))
			//{
				//consumableWeapon->GetOnConsumeDelegate().AddDynamic(OwnerPlayer.Get(), &AActionCharacter::DropWeapon);
				//FScriptDelegate delegate;
				//delegate.BindUFunction(OwnerPlayer)
			//}
			WeaponInstances.Add(pair.Key, weapon); // 인스턴스 맵에 추가
			//WeaponInstances[pair.Key] = weapon; 
		}
	}
}

