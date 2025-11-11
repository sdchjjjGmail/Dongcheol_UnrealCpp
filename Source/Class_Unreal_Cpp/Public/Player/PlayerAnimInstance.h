// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class AActionCharacter;

/**
 * 
 */
UCLASS()
class CLASS_UNREAL_CPP_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Animation")
	TObjectPtr<AActionCharacter> Owner = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Animation")
	TObjectPtr<class UCharacterMovementComponent> Movement = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Animation")
	//FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Animation")
	float MoveSpeed = 0.0f;
};
