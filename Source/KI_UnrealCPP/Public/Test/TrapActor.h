// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapActor.generated.h"

UCLASS()
class KI_UNREALCPP_API ATrapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActivateTrap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex,
		bool bFromSweep, 
		const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Practice")
	TObjectPtr<UStaticMeshComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Practice")
	TObjectPtr<class USphereComponent> TrapOverlap = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Practice")
	TObjectPtr<class UNiagaraComponent> Effect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Practice")
	TObjectPtr<class UDamageType> DamageType = nullptr;
};
