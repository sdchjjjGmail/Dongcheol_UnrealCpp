// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Enemy/DamagePopupActor.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);

	SubMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubMesh"));
	SubMesh->SetupAttachment(RootMesh);

	DamageDisplayPoint = CreateDefaultSubobject<USceneComponent>(TEXT("DamageDisplayPoint"));
	DamageDisplayPoint->SetupAttachment(RootMesh);

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

float AEnemyPawn::TakeDamage(
	float Damage,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Got Damage : %.2f"), Damage);

	ADamagePopupActor* damagePopupActor = GetWorld()->SpawnActor<ADamagePopupActor>(
		DamageDisplayActor.Get(),
		DamageDisplayPoint->GetComponentLocation(),
		FRotator());
	if (damagePopupActor)
	{
		damagePopupActor->PopupActivate(Damage);
	}
	return Damage;
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

