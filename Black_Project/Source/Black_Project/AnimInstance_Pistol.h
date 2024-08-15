// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class BLACK_PROJECT_API UAnimInstance_Pistol : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeInitializAnimation();

	UFUNCTION(BlueprintCallable, Category = "Animation Properties")
	void UpdateAnimationProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	class APawn* Pawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Main")
	class AMain* Main;
};
