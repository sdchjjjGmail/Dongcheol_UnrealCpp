// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Shop/ShopNpcPawn.h"

// Sets default values
AShopNpcPawn::AShopNpcPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShopNpcPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AShopNpcPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AShopNpcPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

