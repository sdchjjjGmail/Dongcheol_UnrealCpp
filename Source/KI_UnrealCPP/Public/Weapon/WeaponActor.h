// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "WeaponActor.generated.h"

UCLASS()
class KI_UNREALCPP_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	virtual void StartOwnerSearch();

public:
	// 공격 활성화/비활성화 하는 함수(컬리전 켜고 끄기)
	UFUNCTION(BlueprintCallable)
	void AttackEnable();
	UFUNCTION(BlueprintCallable)
	void AttackDisable();

	// 공격을 했을 때 실행되어야 할 함수
	UFUNCTION(BlueprintCallable)
	virtual void OnAttack() {};

	UFUNCTION(BlueprintCallable)
	virtual void OnWeaponPickedup(ACharacter* InOwner);

	virtual void PostInitializeComponents() override;

private:
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCapsuleComponent> WeaponCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TSubclassOf<UDamageType> DamageType = nullptr;

	FTimerHandle ownerSearchTimer;

	TWeakObjectPtr<ACharacter> WeaponOwner = nullptr;

	class AActionCharacter* ownerCharacter = nullptr;

	float OwnerSearchFrequency = 0.1f;

private:

};
