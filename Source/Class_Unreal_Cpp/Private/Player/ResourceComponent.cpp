// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ResourceComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Stamina = MaxStamina;
	SetCurrentHealth(MaxHealth);
	SetCurrentStamina(MaxStamina);
	// ...
	
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResourceComponent::AddStamina(float InValue)
{
	// 스태미너를 소비하고 일정 시간 뒤에 자동재생되게 타이머 세팅
	StaminaAutoRegenCoolTimerSet();

	if (Stamina <= 0)
	{
		Stamina = 0.0f;
		// 델리게이트로 스태미너가 떨어졌음을 알림

		OnStaminaEmpty.Broadcast();
	}
	UE_LOG(LogTemp, Log, TEXT("CurrentStamina : (%.1f)"), Stamina);
	SetCurrentStamina(FMath::Clamp(Stamina + InValue, 0, MaxStamina));
}

void UResourceComponent::AddHealth(float InValue)
{
	SetCurrentHealth(FMath::Clamp(Health + InValue, 0, MaxHealth));
	if (!IsAlive())
	{
		OnDie.Broadcast();
	}
}

void UResourceComponent::StaminaAutoRegenCoolTimerSet()
{
	GetWorld()->GetTimerManager().SetTimer(
		StaminaAutoRegenCoolTimer,
		[this]() {

			GetWorld()->GetTimerManager().SetTimer(
				StaminaRegenTickTimer,
				this,
				&UResourceComponent::StaminaRegenPerTick,
				StaminaTickInterval,
				true,
				StaminaTickInterval
			);

		},
		StaminaRegenCooltime,
		false
	);
}

void UResourceComponent::StaminaRegenPerTick()
{
	float stamina = Stamina + StaminaRegenAmount;
	if (stamina > MaxStamina)
	{
		Stamina = MaxStamina;
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTickTimer);
	}
	UE_LOG(LogTemp, Log, TEXT("CurrentStamina : (%.1f)"), Stamina);
	SetCurrentStamina(FMath::Clamp(stamina, 0, MaxStamina));
}

