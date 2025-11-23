// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamagePopupPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KI_UNREALCPP_API UDamagePopupPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamagePopupPoolComponent();

	// 처음 생성할 개수
	UPROPERTY(EditAnywhere, Category = "Pool")
	int32 InitialPoolSize = 10;

	// 사용할 위젯 클래스 (WBP_DamagePopup)
	UPROPERTY(EditAnywhere, Category = "Pool")
	TSubclassOf<class UDamageWidget> DamagePopupClass;

	// 팝업 하나 빌려오기
	UDamageWidget* AcquirePopupWidget();

	// 팝업 반환 (위젯 쪽에서 애니 종료 시 호출)
	void ReleasePopupWidget(UDamageWidget* Widget);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 아직 사용 안 하는 위젯
	TArray<UDamageWidget*> InactivePool;

	// 사용 중 위젯 (디버깅용으로만 써도 됨)
	TArray<UDamageWidget*> ActiveWidgets;

	// 내부 생성 함수
	UDamageWidget* CreateNewPopupWidget();

public:	
	
		
};
