// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "UI/DamageWidget.h"
#include "UI/DamagePopupPoolComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage <= 0.f) return 0.f;

	Health -= ActualDamage;

	ShowDamagePopup(ActualDamage);

	if (Health <= 0.f)
	{
		// 죽는 처리
		Destroy();
	}

	return ActualDamage;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// 월드에서 PoolComponent 찾기 (간단한 방식, 나중에 Subsystem으로 빼도 됨)
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		DamagePopupPool = PC->FindComponentByClass<UDamagePopupPoolComponent>();
	}
}

void AEnemyBase::ShowDamagePopup(float DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("ShowDamagePopup! %f"), DamageAmount);
	if (!DamagePopupPool) 
	{
		return;
	}

	if (UDamageWidget* Popup = DamagePopupPool->AcquirePopupWidget())
	{
		UE_LOG(LogTemp, Warning, TEXT("valid DamagePopupPool"));
		Popup->SetDamageValue(FMath::RoundToInt(DamageAmount));
		Popup->TargetActor = this;
		Popup->PlayPopup();
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

