// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ActionCharacter.h"
#include "Player/StatusComponent.h"
#include "NiagaraComponent.h"

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

	WeaponSlashEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	WeaponSlashEffect->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AWeaponActor::OnWeaponBeginOverlap);
	//StartOwnerSearch();
	WeaponSlashEffect->SetVisibility(false);
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

void AWeaponActor::WeaponActivate(bool bActivate)
{
	//SetActorHiddenInGame(!bActivate); // 무기는 visibility만 수정하면 된다.
	if (bActivate)
	{
		// 무기 활성화
		AttachToComponent(
			WeaponOwner->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("hand_rSocket")); // 플레이어의 손에 붙이가
		SetActorHiddenInGame(false);

		//SetActorHiddenInGame(false);
		//SetActorHiddenInGame(false);
		//SetActorEnableCollision(true);
		//SetActorTickEnabled(true);

		OnWeaponActivate();
	}
	else
	{
		// 무기 비활성화
		SetActorHiddenInGame(true);
		AttachToComponent(
			WeaponOwner->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("root"));
		SetActorRelativeLocation(FVector(0.0f, 0.0f, -10000.0f));

		//SetActorHiddenInGame(true);

		OnWeaponDeActivate();
	}

	// Visibility - O
	// 충돌 - X
	// 액터의 틱 - X
	// 액터의 컴포넌트들의 틱 - X
	// 물리 - X
	// 타이머 - X
	// 오디오 - X
	// 파티클 - X
	// 애니메이션 - X
	// Movement 컴포넌트 - X

	//TSet<UActorComponent*> components = GetComponents();
	//for (auto comp : components)
	//{
	//	// 자식 컴포넌트들 전부 끄기
	//}
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

void AWeaponActor::TrailEnable()
{
	WeaponSlashEffect->SetVisibility(true);
}

void AWeaponActor::TrailDisable()
{
	WeaponSlashEffect->SetVisibility(false);
}

void AWeaponActor::OnWeaponPickedup(int32 InCount)
{
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
