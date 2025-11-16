// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ReinforcedWeaponActor.h"
#include "Player/ActionCharacter.h"
#include "Components/CapsuleComponent.h"

AReinforcedWeaponActor::AReinforcedWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponEquipCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("EquipCollision"));
	WeaponEquipCollision->SetupAttachment(WeaponMesh);
	WeaponEquipCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void AReinforcedWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	UsageCount = 3;
	WeaponEquipCollision->OnComponentBeginOverlap.AddDynamic(this, &AReinforcedWeaponActor::EquipWeapon);
}

void AReinforcedWeaponActor::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	Super::OnWeaponBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	ConsumeUsageCount();
}

void AReinforcedWeaponActor::EquipWeapon(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equip!"));
	ownerCharacter = Cast<AActionCharacter>(OtherActor);
	
	if (ownerCharacter)
	{
		ownerCharacter->SetCurrentWeapon(this);
		ownerCharacter->EquipThisWeapon(this);
	}
	WeaponEquipCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnWeaponEquipCollision.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("owner : %s"), *ownerCharacter->GetName());
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
