// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputMappingContext.h"

void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());	// Subsystem 가져오기 시도
	if (Subsystem)	// Subsystem이 null이 아니면
	{
		Subsystem->AddMappingContext(DefaultMappingContext, GameInputPriority);
	}

	PlayerCameraManager->ViewPitchMax = VewPitchMax;
	PlayerCameraManager->ViewPitchMin = VewPitchMin;
}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(InputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		//UE_LOG(LogTemp, Log, TEXT("바인드 성공"));
		enhanced->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AActionPlayerController::OnLookInput);
		enhanced->BindAction(IA_InventoryOnOff, ETriggerEvent::Started, this, &AActionPlayerController::OnInventoryOnOff);
	}
}

void AActionPlayerController::OnLookInput(const FInputActionValue& InValue)
{
	FVector2D lookAxis = InValue.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("OnLookInput : %s"), *lookAxis.ToString());
	AddYawInput(lookAxis.X);
	AddPitchInput(lookAxis.Y);
}

void AActionPlayerController::OnInventoryOnOff()
{
	if (MainHudWidget.IsValid())
	{
		if (MainHudWidget->GetOpenState() == EOpenState::Open)
		{
			CloseInventoryWidget();
		}
		else
		{
			OpenInventoryWidget();
		}
	}
}

void AActionPlayerController::OpenInventoryWidget()
{
	if (MainHudWidget.IsValid())
	{
		MainHudWidget->OpenInventory();

		//FInputModeGameOnly : 게임 전용(입력이 플레이어 컨트롤러로 우선 전달됨, 마우스 커서가 안보임)
		//FInputModeUIOnly : UI가 떠있을 때 사용(입력이 UI로 먼저 전달됨, 마우스 커서가 보임)
		//FInputModeGameAndUI : 마우스를 클릭했을 때 UI가 아래에 있으면 UI로 처리, 없으면 Game으로 처리

		bShowMouseCursor = true;
	}
}

void AActionPlayerController::CloseInventoryWidget()
{
	if (MainHudWidget.IsValid())
	{
		bShowMouseCursor = false;
		MainHudWidget->CloseInventory();
	}
}
