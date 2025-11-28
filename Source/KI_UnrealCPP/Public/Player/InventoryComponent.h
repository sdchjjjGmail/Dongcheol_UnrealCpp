// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FInvenSlot
{
	GENERATED_BODY()

public:

};

// 여러개의 아이템 슬롯을 가진다.
// 하나의 슬롯에는 한 종류의 아이템만 들어간다.
// 아이템 종류에 따라 한 슬롯에 중첩될 수 있는 아이템 갯수가 달라질 수 있다.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KI_UNREALCPP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 InventorySize = 4;
};
