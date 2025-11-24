// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/CameraShakeAnimNotify.h"

void UCameraShakeAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!CamaraManager.IsValid())
	{
		UWorld* world = MeshComp->GetWorld();
		if (world)
		{
			CamaraManager = world->GetFirstPlayerController()->PlayerCameraManager;
		}
	}

	if (CameraShake && CamaraManager.IsValid())
	{
		CamaraManager->StartCameraShake(CameraShake);
	}
}
