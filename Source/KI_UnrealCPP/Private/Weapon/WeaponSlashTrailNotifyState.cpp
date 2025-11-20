// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponSlashTrailNotifyState.h"
#include "Player/ActionCharacter.h"

void UWeaponSlashTrailNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}

	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->SetTrailState(true);
	}
}

void UWeaponSlashTrailNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->SetTrailState(false);
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
