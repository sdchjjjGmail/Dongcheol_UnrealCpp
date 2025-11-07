// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); // 씬 컴포넌트 하나 만들기
	SetRootComponent(root); // 루트로 지정

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BdoyMesh")); // 스태틱 메시 컴포넌트 하나 만들기
	BodyMesh->SetupAttachment(root); // root 아래에 붙이기
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	//BodyMesh->SetRelativeLocation(FVector(0, 0, 100));
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Log, TEXT("VAL: %f"), (FMath::Cos(CosAlpha)));

	OnFloatingMeshUpdate(DeltaTime);
}

void AFloatingActor::OnFloatingMeshUpdate(float DeltaTime)
{
	// 회전 적용
	BodyMesh->AddRelativeRotation(DeltaTime * SpinSpeed * FRotator(0, 1, 0));

	ElapsedTime += DeltaTime; // 시간 누적시키기

	// Cos 함수 이용해서 위치기준 업데이트
	CosAlpha = FMath::Cos(ElapsedTime); 
	CosAlpha += 1;
	CosAlpha *= 0.5f;
	CosAlpha = 1 - CosAlpha;

	//위치 적용
	BodyMesh->SetRelativeLocation(CosAlpha * FVector(0, 0, CosAlpha * MoveHeight));
}

