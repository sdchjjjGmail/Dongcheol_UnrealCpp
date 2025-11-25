// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ANS_WeaponCollisionTrigger.h"
#include "Player/ActionCharacter.h"

void UANS_WeaponCollisionTrigger::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}
	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->SetCollisionOn();
	}
}

void UANS_WeaponCollisionTrigger::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->SetCollisionOff();
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
