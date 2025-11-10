// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SocketOffset = FVector(0, 0, 250);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhanced) // 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AActionCharacter::OnMoveInput);
		enhanced->BindAction(IA_PlayerView, ETriggerEvent::Triggered, this, &AActionCharacter::OnCaneraMoveInput);
	}
}

void AActionCharacter::OnMoveInput(const FInputActionValue& InValue)
{
	FVector2D InputDirection = InValue.Get<FVector2D>();

	UE_LOG(LogTemp, Log, TEXT("Dir : (%.1f, %.1f)"), InputDirection.X, InputDirection.Y);
	UE_LOG(LogTemp, Log, TEXT("Dir : (%s)"), *InputDirection.ToString());

	AddMovementInput(FVector(InputDirection.Y, InputDirection.X, 0));
	//AddActorLocalOffset(FVector(InputDirection.Y, InputDirection.X, 0) * MoveSpeed);
}

void AActionCharacter::OnCaneraMoveInput(const FInputActionValue& InValue)
{

	FVector2D InputDirection = InValue.Get<FVector2D>();
	UE_LOG(LogTemp, Log, TEXT("Mouse Input Value : (%s)"), *InputDirection.ToString());

}

