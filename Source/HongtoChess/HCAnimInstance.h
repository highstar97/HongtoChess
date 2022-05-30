// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HONGTOCHESS_API UHCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UHCAnimInstance();

	void PlayAttackMontage(int32 AttackSpeed);

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
