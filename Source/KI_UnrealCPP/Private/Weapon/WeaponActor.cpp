// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ActionCharacter.h"
#include "Player/StatusComponent.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(root);
	//WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	WeaponCollision->SetupAttachment(WeaponMesh);
	WeaponCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AWeaponActor::OnWeaponBeginOverlap);
	StartOwnerSearch();
}

void AWeaponActor::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	float finalDamage = Damage;
	AController* instigator = nullptr;
	if (ownerCharacter)
	{
		if (ownerCharacter == OtherActor)
		{
			return;
		}
		if (ownerCharacter->GetStatusComponent() != nullptr)
		{
			finalDamage += ownerCharacter->GetStatusComponent()->GetAttackPower();
		}
		instigator = ownerCharacter->GetController();
	}
	UE_LOG(LogTemp, Log, TEXT("ApplyDamage : %s"), *OtherActor->GetName());
	UGameplayStatics::ApplyDamage(OtherActor, finalDamage, instigator, this, DamageType);
}

void AWeaponActor::AttackEnable()
{
	UE_LOG(LogTemp, Log, TEXT("Hit On"));
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWeaponActor::AttackDisable()
{
	UE_LOG(LogTemp, Log, TEXT("Hit Off"));
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponActor::OnWeaponPickedup(ACharacter* InOwner)
{
	WeaponOwner = InOwner;
}

void AWeaponActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// CDO(Class Default Object)의 설정대로 초기화 된 이후( = OverlapOnlyPawn 설정 이후)
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponActor::StartOwnerSearch()
{
	GetWorld()->GetTimerManager().SetTimer(
		ownerSearchTimer,
		[this]() {
			if (WeaponOwner.IsValid())
			{
				ownerCharacter = Cast<AActionCharacter>(WeaponOwner.Get());
				if (ownerCharacter)
				{
					UE_LOG(LogTemp, Log, TEXT("ownerCharacter : %s"), *ownerCharacter->GetName());
					ownerCharacter->OnWeaponCollisionOn.AddDynamic(this, &AWeaponActor::AttackEnable);
					ownerCharacter->OnWeaponCollisionOff.AddDynamic(this, &AWeaponActor::AttackDisable);
					GetWorld()->GetTimerManager().ClearTimer(ownerSearchTimer);
				}
			}
		},
		OwnerSearchFrequency,
		true
	);
}
