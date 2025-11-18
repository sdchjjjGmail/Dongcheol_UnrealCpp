// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Pickupable.h"
#include "Common/CommonEnums.h"
#include "PickupActor.generated.h"

UCLASS()
class KI_UNREALCPP_API APickupActor : public AActor, public IPickupable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// IPickupable의 구현
	virtual void OnPickup_Implementation(AActor* Target) override;

	// 픽업에 힘을 가해서 날리는 함수
	void AddImpulse(FVector& Velocity);

private:
	UFUNCTION()
	void OnPickupBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTimelineUpdate(float Value);
	UFUNCTION()
	void OnTimelineFinish();

protected:
	// 물리 적용용 루트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USphereComponent> BaseRoot = nullptr;

	// 아이템 외형
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Mesh = nullptr;

	// 아이템 획득 처리용 overlap collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USphereComponent> PickupOverlap = nullptr;

	// 아이템 이펙트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UNiagaraComponent> Effect = nullptr;

	// 타임라인 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr <class UTimelineComponent> PickupTimeline = nullptr;

	// 이 픽업을 먹었을 때 얻을 무기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	EItemCode PickupItem = EItemCode::BasicWeapon;

	// 스폰 후에 먹을 수 있기 될 때까지의 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float PickupableTime = 3.0f;

	// 아이템 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RotateSpeed = 180.0f;

	// 픽업 획득 효과용 거리 보간 커브
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UCurveFloat> DistanceCurve = nullptr;

	// 픽업 획득 효과용 높이 커브
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UCurveFloat> HeightCurve = nullptr;

	// 픽업 획득 효과용 스케일 커브
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UCurveFloat> ScaleCurve = nullptr;

	// 아이템 획득에 걸리는 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	float Duration = 0.5f;

	// 아이템 획득 시 튀어오르는 높이
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	float PickupHeight = 50.0f;

private:
	// 이 픽업 아이템을 먹은 액터
	TWeakObjectPtr<AActor> PickupOwner = nullptr;

	// 주워졌다
	bool bPickedup = false;

	FVector PickupStartLocation = FVector(0, 0, 0);

	// 스폰 직후 먹지 못하는 시간동안 처리하는 타이머 핸들
	FTimerHandle PickupableTimerHandle;
};
