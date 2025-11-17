// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumableActor.h"

// Sets default values
AConsumableActor::AConsumableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConsumableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConsumableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

