// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TrapActor.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

// Sets default values
ATrapActor::ATrapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TrapOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	TrapOverlap->SetupAttachment(Root);
	TrapOverlap->SetSphereRadius(100.0f);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Root);
	Effect->SetRelativeLocation(FVector(0, 0, 50));
}

// Called when the game starts or when spawned
void ATrapActor::BeginPlay()
{
	Super::BeginPlay();
	TrapOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATrapActor::ActivateTrap);
	Effect->SetVisibility(false);
}

void ATrapActor::ActivateTrap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Step on Trap!"));
	Effect->SetVisibility(true);
	//Effect->SetColorParameter(TEXT("Effectcolor"), InColor);
	Effect->ResetSystem();
}

// Called every frame
void ATrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

