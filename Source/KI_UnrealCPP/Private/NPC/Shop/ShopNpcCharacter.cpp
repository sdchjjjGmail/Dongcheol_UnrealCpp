// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Shop/ShopNpcCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Player/ActionCharacter.h"

// Sets default values
AShopNpcCharacter::AShopNpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShopArea = CreateDefaultSubobject<UCapsuleComponent>("ShopArea");
	ShopArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShopNpcCharacter::BeginPlay()
{
	Super::BeginPlay();
	ShopArea->OnComponentBeginOverlap.AddDynamic(this, &AShopNpcCharacter::EnableShop);
}

void AShopNpcCharacter::EnableShop(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Entered Shop Area %s"), *OtherActor->GetName());
	//if (OtherActor == GetWorld()->)
}

// Called every frame
//void AShopNpcCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AShopNpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AShopNpcCharacter::PrepareShop_Implementation(AActionCharacter* InPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("PrepareShop"));
	Player = InPlayer;
	if (Player.IsValid() && MyItemTable)
	{
		Player->SetShopAvailable(true, MyItemTable, this);
	}
}

void AShopNpcCharacter::DisableShop_Implementation()
{
	if (Player.IsValid()) Player->SetShopAvailable(false, nullptr, nullptr);
}

void AShopNpcCharacter::OpenShop_Implementation()
{

}

void AShopNpcCharacter::CloseShop_Implementation()
{
	Destroy();
}
