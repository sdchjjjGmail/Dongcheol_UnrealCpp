// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupActor.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include <Interface/InventoryOwner.h>

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 루트 : 컬리전 추가(sphere)
	// 무기 외형 : 스켈레탈 메시
	// 오버랩 영역 : 스피어 컬리전
	// 이팩트 : 그대로

	BaseRoot = CreateDefaultSubobject<USphereComponent>(TEXT("BastRoot"));
	SetRootComponent(BaseRoot);
	BaseRoot->InitSphereRadius(1.0f);
	BaseRoot->SetSimulatePhysics(true);
	BaseRoot->BodyInstance.bLockXRotation = true;
	BaseRoot->BodyInstance.bLockYRotation = true;
	BaseRoot->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BaseRoot);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->AddRelativeRotation(FRotator(0, 0, -10.0f));

	PickupOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	PickupOverlap->SetupAttachment(BaseRoot);
	PickupOverlap->SetSphereRadius(100.0f);
	PickupOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(BaseRoot);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	if (PickupOverlap)
	{
		PickupOverlap->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnPickupBeginOverlap);
	}
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddWorldRotation(FRotator(0, RotateSpeed * DeltaTime, 0));
}

void APickupActor::OnPickup_Implementation(AActor* Target)
{
	UE_LOG(LogTemp, Log, TEXT("Pickup Interface Overlap"));
	// 자신을 먹은 대상에게 자기가 가지고 있는 무기를 알려줘야 함
	if (Target && Target->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(Target, PickupItem);
	}
}

void APickupActor::OnPickupBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Pickup Overlap"));
}
