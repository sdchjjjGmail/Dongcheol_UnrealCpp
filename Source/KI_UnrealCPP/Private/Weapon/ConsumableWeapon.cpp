// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ConsumableWeapon.h"

void AConsumableWeapon::BeginPlay()
{
	Super::BeginPlay();
	RemainingUseCount = MaxUseCount;
}

void AConsumableWeapon::OnAttack()
{
	RemainingUseCount--;
	if (RemainingUseCount <= 0)
	{
		OnWeaponUseEnded.Broadcast();
	}
}

// 무기를 획득했을 때 실행되는 함수
void AConsumableWeapon::OnWeaponPickedup(int32 InCount)
{
	// 현재 사용되는 곳 없음
	Super::OnWeaponPickedup(InCount);
	RemainingUseCount = InCount;
}

void AConsumableWeapon::OnWeaponActivate()
{
	RemainingUseCount = MaxUseCount;
}
