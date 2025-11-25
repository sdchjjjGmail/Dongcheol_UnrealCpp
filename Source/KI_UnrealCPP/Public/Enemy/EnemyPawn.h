// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Common/CommonStructures.h"
#include "EnemyPawn.generated.h"

UCLASS()
class KI_UNREALCPP_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual float TakeDamage(
	//	float Damage,
	//	FDamageEvent const& DamageEvent, 
	//	AController* EventInstigator,
	//	AActor* DamageCauser
	//) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TestDropItem() { DropItems(); };

private:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void DropItems();

	UFUNCTION()
	void OnDie();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UStaticMeshComponent> RootMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UStaticMeshComponent> SubMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<USceneComponent> DamageDisplayPoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class UResourceComponent> Resource = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|UI")
	TSubclassOf<class ADamagePopupActor> DamageDisplayClass = nullptr;

private:
	bool bInvincible = false;
	FTimerHandle InvincibleTimer;
	float LastDamage = 0.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items")
	TArray<FItemDropInfo> DropItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Item")
	TObjectPtr<class UDataTable> DropItemTable = nullptr;
};
