// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// generated.h는 모든 헤더 중 마지막에 있어야 한다.
#include "TestActor.generated.h"

// UCLASS()
// - C++ 클래스를 언리얼 엔진의 객체 시스템에 등록(=UObject)
// - 이 매크로가 붙은 클래스만이 언리얼엔진의 객체로 인식되고 관리된다
// - 주요 기능
//   - 가비지 콜랙팅
//   - 블루프린트 연동
//   - 에디터 노출

// UFUNCTION()
//  - 블루프린트에서 함수를 호출, 구현, 재정의 등을 할 때 UFUNCTION 사용
//  - 다이나믹 델리게이트에 바인딩 할 경우 UFUNCTION 필수
//  - 블루프린트에서 사용될 경우에 반드시 필요하다

UCLASS()
class CLASS_UNREAL_CPP_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Test_NormalFunction();

	UFUNCTION(BlueprintCallable, Category = "내 함수") // C++로 작성한 함수를 블루프린트에서 호출할 수 있다.
	void Test_UFunction(bool bCheck);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "내 함수")  // C++에서 선언만 하고 구현은 블루프린트에서
	void Test_ImplementableFunction();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "내 함수") // C++에서 구현은 했는데 블루프린트에서 재정의(Override) 하고싶은 경우
	void Test_NativeFunction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
