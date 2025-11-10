// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAnimInstance.h"
#include "Player/ActionCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{

}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Owner = Cast<AActionCharacter>(GetOwningActor());

	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Movement)
	{
		UE_LOG(LogTemp, Log, TEXT("GetLastMovementInputVector : (%s)"), *Owner->GetLastMovementInputVector().ToString());
		MoveSpeed = Owner->GetLastMovementInputVector().Length() * Movement->MaxWalkSpeed;
	}
}
