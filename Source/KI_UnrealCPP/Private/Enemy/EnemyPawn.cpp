// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Enemy/DamagePopupActor.h"
#include "Framework/DamagePopupSubsystem.h"
#include "Framework/EnemyTrackingSubsystem.h"
#include "Framework/PickupFactorySubsystem.h"
#include "Player/ResourceComponent.h"
#include "Data/DropItemData_TableRow.h"
#include "Item/PickupActor.h"

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

		UE_LOG(LogTemp, Log, TEXT("Current Health : %.2f"), Resource->GetCurrentHealth());

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

void AEnemyPawn::DropItems()
{
	//for (const auto& item : DropItemInfo)
	//{
	//	item.DropRate;
	//	item.DropItemClass;
	//}

	if (DropItemTable)
	{
		UPickupFactorySubsystem* factorySystem = GetWorld()->GetSubsystem<UPickupFactorySubsystem>();
		if (!factorySystem)
		{
			UE_LOG(LogTemp, Warning, TEXT("invalid factorySystem"));
			return;
		}
		factorySystem->DropEnemyItem(DropItemTable, GetActorLocation(), GetActorRotation());

		//TArray<FDropItemData_TableRow> AllRows;
		//DropItemTable->GetAllRows<FDropItemData_TableRow>(TEXT("Rows"), AllRows);

		//APickupActor* pickup = nullptr;

		//TMap<FName, uint8*> RowMap = DropItemTable->GetRowMap();

		// 중복으로 당첨 가능
		//for (const auto& element : RowMap)
		//{
		//	FDropItemData_TableRow* row = (FDropItemData_TableRow*)element.Value;
		//	if (FMath::FRand() <= row->DropRate)
		//	{
		//		GetWorld()->SpawnActor<APickupActor>(
		//			row->DropItemClass,
		//			GetActorLocation() + FVector::UpVector * 100.0f,
		//			GetActorRotation()
		//		);
		//	}
		//}

		// 전체 가중치 사용하는 방식(한개만 뽑기)
		//float totalWeight = 0.0f;
		//for (const auto& element : RowMap)
		//{
		//	FDropItemData_TableRow* row = (FDropItemData_TableRow*)element.Value;
		//	totalWeight += row->DropRate;
		//}
		//float randomSelect = FMath::FRandRange(0, totalWeight);
		//float currentWeight = 0.0f;
		//for (const auto& element : RowMap)
		//{
		//	FDropItemData_TableRow* row = (FDropItemData_TableRow*)element.Value;
		//	currentWeight += row->DropRate;
		//	if (randomSelect < currentWeight)
		//	{
		//		// 당첨 -> 스폰처리
		//		GetWorld()->SpawnActor<APickupActor>(
		//			row->DropItemClass,
		//			GetActorLocation() + FVector::UpVector * 200.0f,
		//			GetActorRotation()
		//		);
		//		break;
		//	}
		//}

		//if (pickup)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("Drop Success : %s"), *pickup->GetName());
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Log, TEXT("Drop Fail"));
		//}
	}
}

void AEnemyPawn::OnDie()
{
	UE_LOG(LogTemp, Log, TEXT("적은 죽었다."));

	DropItems();
	Destroy();
}
