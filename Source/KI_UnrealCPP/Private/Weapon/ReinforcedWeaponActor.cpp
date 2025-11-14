// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ReinforcedWeaponActor.h"
#include "Player/ActionCharacter.h"

void AReinforcedWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	UsageCount = 3;
}

void AReinforcedWeaponActor::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::OnWeaponBeginOverlap(OverlappedActor, OtherActor);
	ConsumeUsageCount();
}

void AReinforcedWeaponActor::StartOwnerSearch()
{
	Super::StartOwnerSearch();
	if (ownerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Equip success!"));
		ownerCharacter->SetCurrentWeapon(this);
	}
}

void AReinforcedWeaponActor::ConsumeUsageCount()
{
	UsageCount -= 1;
	UE_LOG(LogTemp, Warning, TEXT("Count : %d"), UsageCount);
	if (UsageCount <= 0)
	{
		OnWeaponDeprecated.Broadcast();
	}
}
