// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MUTANT_RAID_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDead;
};
