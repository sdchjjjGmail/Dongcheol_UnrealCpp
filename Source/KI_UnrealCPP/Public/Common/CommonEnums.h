// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemCode : uint8
{
	BasicWeapon UMETA(DisplayName = "기본무기"),
	Axe         UMETA(DisplayName = "도끼"),
	Saw			UMETA(DisplayName = "톱"),
	Cup			UMETA(DisplayName = "금잔"),
	Gem			UMETA(DisplayName = "보석"),
	PotionHealth UMETA(DisplayName = "힐링 포션"),
	PotionStamina UMETA(DisplayName = "스테미너 포션"),
	Gold		UMETA(DisplayName = "골드")
};

UENUM(BlueprintType)
enum class EWeaponCode : uint8
{
	BasicWeapon UMETA(DisplayName = "기본무기"),
	Axe         UMETA(DisplayName = "도끼"),
	Saw			UMETA(DisplayName = "톱"),
};

// 비트플래그용 enum. 에디터에서 편집 가능
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBitFlag : uint8
{
	None = 0,
	Test = 1 << 0,
	Test2 = 1 << 1,
	Test3 = 1 << 2,
	Test4 = 1 << 3,
	Test5 = 1 << 4,
};

// Cpp에서 bitflag 변수 만들때
//UPROPERTY(EditAnywhere, meta = (Bitmask, NitmaskEnum = "EBitFlag"))
//int32 BitflagSample

//(블루프린트에서 변수로 만들었을 경우는 int로 변수를 만들고 enum 타입을 설정)
