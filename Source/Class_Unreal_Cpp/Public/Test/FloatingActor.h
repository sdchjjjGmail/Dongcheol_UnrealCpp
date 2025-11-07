// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class CLASS_UNREAL_CPP_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 스태틱매시 움직임 업데이트 하는 함수
	virtual void OnFloatingMeshUpdate(float DeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 100.0f;
	float MoveHeight = 300.0f;
	float SpinSpeed = 100;
	float CosAlpha = 0.0f;
	float ElapsedTime = 0.0f;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BodyMesh = nullptr;

};
