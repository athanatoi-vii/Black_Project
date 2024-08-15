// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Pistol.h"
#include "Main.h"

void UAnimInstance_Pistol::NativeInitializAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}

void UAnimInstance_Pistol::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}