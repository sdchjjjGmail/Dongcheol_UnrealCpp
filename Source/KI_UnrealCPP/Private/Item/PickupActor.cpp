// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupActor.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
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
	//PickupOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn")); // 생성 직후는 바로 먹을 수 없다.
	PickupOverlap->SetCollisionProfileName(TEXT("NoCollision"));

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(BaseRoot);

	PickupTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("PickupTimeline"));
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	if (PickupOverlap)
	{
		PickupOverlap->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnPickupBeginOverlap);
	}

	if (PickupTimeline)
	{
		if (DistanceCurve)
		{
			FOnTimelineFloat UpdateDelegate;
			UpdateDelegate.BindUFunction(this, FName("OnTimelineUpdate"));
			PickupTimeline->AddInterpFloat(DistanceCurve, UpdateDelegate);

			FOnTimelineEvent FinishDelegate;
			FinishDelegate.BindUFunction(this, FName("OnTimelineFinish"));
			PickupTimeline->SetTimelineFinishedFunc(FinishDelegate);
		}

		PickupTimeline->SetPlayRate(1 / Duration);
	}

	FTimerManager& timerManager = GetWorldTimerManager();
	timerManager.ClearTimer(PickupableTimerHandle);
	timerManager.SetTimer(
		PickupableTimerHandle,
		[this]() {
			PickupOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
		},
		PickupableTime,
		false);

	bPickedup = false;
	PickupCount = 5;
}
// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddWorldRotation(FRotator(0, RotateSpeed * DeltaTime, 0));
}

void APickupActor::OnPickup_Implementation(AActor* Target)
{
	if (!bPickedup)
	{
		PickupOwner = Target;
		PickupStartLocation = Mesh->GetRelativeLocation() + GetActorLocation(); // Mesh의 월드 위치

		PickupTimeline->PlayFromStart();

		bPickedup = true;
		this->SetActorEnableCollision(ECollisionEnabled::NoCollision);
		BaseRoot->SetSimulatePhysics(false);
	}
}

void APickupActor::AddImpulse(FVector& Velocity)
{
	BaseRoot->AddImpulse(Velocity, NAME_None, true);
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

void APickupActor::OnTimelineUpdate(float Value)
{
	// 타임라인의 정규화 된 진행 시간(0~1)
	float currentTime = PickupTimeline->GetPlaybackPosition();
	UE_LOG(LogTemp, Log, TEXT("currentTime : %.2f"), currentTime);

	// 커브의 현재 값 받아오기
	float distanceValue = Value;
	float heightValue = HeightCurve ? HeightCurve->GetFloatValue(currentTime) : 0.0f;
	float scaleCurve = ScaleCurve ? ScaleCurve->GetFloatValue(currentTime) : 1.0f;

	// 커브값을 기준으로 새 위치와 스케일 계산
	FVector NewLocation = FMath::Lerp(
		PickupStartLocation, PickupOwner.Get()->GetActorLocation(), distanceValue);
	NewLocation += heightValue * PickupHeight * FVector::UpVector;

	Mesh->SetWorldLocation(NewLocation);

	FVector NewScale = FVector::One() * scaleCurve;
	Mesh->SetRelativeScale3D(NewScale);
}

void APickupActor::OnTimelineFinish()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem, PickupCount);
	}
	Destroy();
}
