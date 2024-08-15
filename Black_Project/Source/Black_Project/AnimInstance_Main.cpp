// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Main.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Main.h"

void UAnimInstance_Main::NativeInitializAnimation()
{
	MovementSpeed = 0.f;
	bIsInAir = false;

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Main = Cast<AMain>(Pawn);
		}
	}
}

void UAnimInstance_Main::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (Main == nullptr)
		{
			Main = Cast<AMain>(Pawn);
		}

		if (Main)
		{
			Main->Main_bIsInAir = bIsInAir;
		}
	}
}