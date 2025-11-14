// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ANS_WeaponCollisionTrigger.h"
#include "Player/ActionCharacter.h"

void UANS_WeaponCollisionTrigger::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	if (OwnerCharacter.IsValid())
	{
		// OwnerCharacter에 자기 자신을 설정
		UE_LOG(LogTemp, Log, TEXT("Notify Hit On"));

		OwnerCharacter->SetCollisionOn();
	}
}

void UANS_WeaponCollisionTrigger::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (OwnerCharacter.IsValid())
	{
		// OwnerCharacter 설정 해제
		UE_LOG(LogTemp, Log, TEXT("Notify Hit Off"));

		OwnerCharacter->SetCollisionOff();
		OwnerCharacter = nullptr;
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
