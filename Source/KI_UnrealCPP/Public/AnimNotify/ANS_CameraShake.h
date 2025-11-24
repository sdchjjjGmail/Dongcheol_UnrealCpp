// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_CameraShake.generated.h"

/**
 * 
 */
UCLASS()
class KI_UNREALCPP_API UANS_CameraShake : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	//virtual void Notify(
	//	USkeletalMeshComponent* MeshComp, 
	//	UAnimSequenceBase* Animation,
	//	const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY()
	TSubclassOf<class UCameraShakeBase> CameraShake = nullptr;
};
