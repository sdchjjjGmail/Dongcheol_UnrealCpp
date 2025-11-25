// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Enemy/DamagePopupActor.h"
#include "Framework/DamagePopupSubsystem.h"
#include "Framework/EnemyTrackingSubsystem.h"
#include "Player/ResourceComponent.h"

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

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("Resource"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AEnemyPawn::OnTakeDamage);

	if (UWorld* world = GetWorld())
	{
		if (UEnemyTrackingSubsystem* enemyTracker = world->GetSubsystem<UEnemyTrackingSubsystem>())
		{
			enemyTracker->RegistEnemy();
		}
	}
}

void AEnemyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* world = GetWorld())
	{
		if (UEnemyTrackingSubsystem* enemyTracker = world->GetSubsystem<UEnemyTrackingSubsystem>())
		{
			enemyTracker->UnregistEnemy();
		}
	}

	Super::EndPlay(EndPlayReason);
}

//float AEnemyPawn::TakeDamage(
//	float Damage,
//	FDamageEvent const& DamageEvent,
//	AController* EventInstigator,
//	AActor* DamageCauser)
//{
//	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
//
//	UE_LOG(LogTemp, Log, TEXT("Got Damage : %.2f"), Damage);
	//GEngine->AddOnScreenDebugMessage();

	//ADamagePopupActor* damagePopupActor = GetWorld()->SpawnActor<ADamagePopupActor>(
	//	DamageDisplayActor.Get(),
	//	DamageDisplayPoint->GetComponentLocation(),
	//	FRotator());
	//if (damagePopupActor)
	//{
	//	damagePopupActor->PopupActivate(Damage);
	//}
	//UDamagePopupSubsystem* popupSystem = GetWorld()->GetSubsystem<UDamagePopupSubsystem>();
	//popupSystem->ShowDamagePopup(Damage, DamageDisplayPoint->GetComponentLocation());
//	return Damage;
//}

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

void AEnemyPawn::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage()

	UE_LOG(LogTemp, Log, TEXT("Current Health : %.2f"), Resource->GetCurrentHealth());

	if (!bInvincible || !FMath::IsNearlyEqual(LastDamage, Damage))
	{
		UE_LOG(LogTemp, Log, TEXT("Got Damage : %.1f"), Damage);

		Resource->AddHealth(-Damage);

		//ADamagePopupActor* actor = GetWorld()->SpawnActor<ADamagePopupActor>(
		//	DamageDisplayClass, DamageDisplayPoint->GetComponentToWorld());
		//if (actor)
		//{
		//	actor->PopupActivate(Damage);
		//}

		UDamagePopupSubsystem* popupSystem = GetWorld()->GetSubsystem<UDamagePopupSubsystem>();
		popupSystem->ShowDamagePopup(Damage, DamageDisplayPoint->GetComponentLocation());

		if (Resource->IsAlive())
		{
			bInvincible = true;
			LastDamage = Damage;

			// this가 파괴되면 람다는 더 이상 실행되지 않는다.
			FTimerDelegate resetdelegate = FTimerDelegate::CreateWeakLambda(
				this,
				[this]()
				{
					bInvincible = false;

				});

			GetWorldTimerManager().ClearTimer(InvincibleTimer);
			GetWorldTimerManager().SetTimer(
				InvincibleTimer,
				resetdelegate,
				0.1f,
				false
			);
		}
		else
		{
			OnDie();
		}
	}

}

void AEnemyPawn::OnDie()
{
	UE_LOG(LogTemp, Log, TEXT("이미 적은 죽었다."));
	Destroy();
}


