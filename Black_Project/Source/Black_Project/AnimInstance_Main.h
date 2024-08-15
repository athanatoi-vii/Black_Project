// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Main.generated.h"

UCLASS()
class BLACK_PROJECT_API UAnimInstance_Main : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeInitializAnimation();

	UFUNCTION(BlueprintCallable, Category = "Animation Properties")
	void UpdateAnimationProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OffsetUpDownAnim")
	float OffsetUpDown_Anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WeponUpDownAnim")
	float WeponUpDown_Anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class APawn* Pawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class AMain* Main;
};
