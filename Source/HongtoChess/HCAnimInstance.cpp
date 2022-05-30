// Fill out your copyright notice in the Description page of Project Settings.


#include "HCAnimInstance.h"

UHCAnimInstance::UHCAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Animations/UE4_Mannequin_Skeleton_Montage.UE4_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UHCAnimInstance::PlayAttackMontage(int32 AttackSpeed)
{
	Montage_Play(AttackMontage, 1.0f/*1.0f/AttackSpeed*/);
	
}
