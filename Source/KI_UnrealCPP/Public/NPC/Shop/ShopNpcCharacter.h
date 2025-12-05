// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HasShop.h"
#include "ShopNpcCharacter.generated.h"

UCLASS()
class KI_UNREALCPP_API AShopNpcCharacter : public ACharacter, public IHasShop
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShopNpcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void EnableShop(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex,
		bool bFromSweep, 
		const FHitResult& SweepResult);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void PrepareShop_Implementation(AActionCharacter* Player) override;
	virtual void DisableShop_Implementation() override;
	virtual void OpenShop_Implementation() override;
	virtual void CloseShop_Implementation() override;

protected: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCapsuleComponent> ShopArea = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AActionCharacter> Player = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<class UDataTable> MyItemTable = nullptr;

private:

};
