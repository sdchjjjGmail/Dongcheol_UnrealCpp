// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_ComboPractice.h"
#include "Player/ActionCharacter.h"

void UAnimNotifyState_ComboPractice::NotifyBegin(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, 
	float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	if (OwnerCharacter.IsValid())
	{
		// OwnerCharacter에 자기 자신을 설정
		OwnerCharacter->SetComboSectionJumpNotify(this);
	}
}

void UAnimNotifyState_ComboPractice::NotifyEnd(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (OwnerCharacter.IsValid())
	{
		// OwnerCharacter 설정 해제
		OwnerCharacter->SetSectionJumpNotify(nullptr);
		OwnerCharacter = nullptr;
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
