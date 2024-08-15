// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/capsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerController_Main.h"
#include "Engine/SkeletalMeshSocket.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
/*
#include "Animation/AnimInstance.h"
*/

AMain::AMain()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 92.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), TEXT("FP_Camera"));
	//Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("FP_Camera"));

	Capsule_Hand = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule_Hand"));
	Capsule_Hand->SetupAttachment(GetMesh(), TEXT("Hand_r"));
	//Capsule_Hand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Hand_r"));
	Capsule_Hand->SetCapsuleSize(15.0f, 32.0f);

	Pistol = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pistol"));
	Pistol->SetupAttachment(GetMesh(), TEXT("Pistol"));
	//Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Pistol"));

	Camera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	Lock_U_Rate = 30.f;
	Lock_R_Rate = 15.f;
	OffsetUpDown = 90.f;
	WeponUpDown = 0.5f;
	fRotate_Reverse = 1.f;
	bStanding = false;
	bAttack = false;
	bOJ = true;

	Main_bIsInAir = false;
}

void AMain::BeginPlay()
{
	Super::BeginPlay();

	// اضافه کردن Enhanced Input Subsystem
	MainPlayerController = Cast<APlayerController_Main>(GetController());
	if (MainPlayerController && InputMapping)
	{
		if (UEnhancedInputLocalPlayerSubsystem* E_I_L_P_S = MainPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			E_I_L_P_S->AddMappingContext(InputMapping, 0);
		}
	}
}

void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MoveInput, ETriggerEvent::Triggered, this, &AMain::Move);
		EnhancedInputComponent->BindAction(IA_LookInput, ETriggerEvent::Triggered, this, &AMain::Look);
		EnhancedInputComponent->BindAction(IA_Standing, ETriggerEvent::Started, this, &AMain::Func_Standing_Start);
		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &AMain::Func_Attack_Start);
		EnhancedInputComponent->BindAction(IA_Standing, ETriggerEvent::Completed, this, &AMain::Func_Standing_End_BP);
		EnhancedInputComponent->BindAction(IA_Standing, ETriggerEvent::Completed, this, &AMain::Func_Standing_End);
		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Completed, this, &AMain::Func_Attack_End);
		EnhancedInputComponent->BindAction(IA_Rotate_R, ETriggerEvent::Triggered, this, &AMain::Rotate_R_BP);
		EnhancedInputComponent->BindAction(IA_Rotate_P, ETriggerEvent::Triggered, this, &AMain::Rotate_P_BP);
		EnhancedInputComponent->BindAction(IA_Rotate_Y, ETriggerEvent::Triggered, this, &AMain::Rotate_Y_BP);
		EnhancedInputComponent->BindAction(IA_Rotate_Reverse, ETriggerEvent::Started, this, &AMain::Rotate_Reverse_Start);
		EnhancedInputComponent->BindAction(IA_Rotate_Reverse, ETriggerEvent::Completed, this, &AMain::Rotate_Reverse_End);
		EnhancedInputComponent->BindAction(IA_Space, ETriggerEvent::Triggered, this, &AMain::Func_Space_BP);
	}
}

// Camera
void AMain::Look(const FInputActionValue& Value)
{
	FVector2D LookLocal = Value.Get<FVector2D>();

	AddControllerYawInput(LookLocal.X * Lock_R_Rate * GetWorld()->GetDeltaSeconds());

	if (OffsetUpDown >= 0.f && OffsetUpDown <= 180.f)
	{
		float Plus_Offset = -(LookLocal.Y * Lock_U_Rate * GetWorld()->GetDeltaSeconds());

		if (OffsetUpDown + Plus_Offset < 0.f)
		{
			OffsetUpDown = 0.f;
		}
		else if (OffsetUpDown + Plus_Offset > 180.f)
		{
			OffsetUpDown = 180.f;
		}
		else
		{
			OffsetUpDown += Plus_Offset;
		}
	}
	else
	{
		OffsetUpDown = 90.f;
	}
	if (WeponUpDown >= 0.f && WeponUpDown <= 1.f)
	{
		float Plus_Wepon = ((LookLocal.Y / 180.f) * Lock_U_Rate * GetWorld()->GetDeltaSeconds());

		if (WeponUpDown + Plus_Wepon < 0.f)
		{
			WeponUpDown = 0.f;
		}
		else if (WeponUpDown + Plus_Wepon > 1.f)
		{
			WeponUpDown = 1.f;
		}
		else
		{
			WeponUpDown += Plus_Wepon;
		}
	}
	else
	{
		WeponUpDown = 0.5f;
	}
}

// Air


// Movement
void AMain::Move(const FInputActionValue& Value)
{ 
	FVector2D MovementLocal = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementLocal.Y);
	AddMovementInput(GetActorRightVector(), MovementLocal.X);
}

// Attaack Override
void AMain::Rotate_R_BP_Implementation(const FInputActionValue& Value) {}

void AMain::Rotate_P_BP_Implementation(const FInputActionValue& Value) {}

void AMain::Rotate_Y_BP_Implementation(const FInputActionValue& Value) {}

void AMain::Func_Standing_End_BP_Implementation(const FInputActionValue& Value) {}

void AMain::Func_Space_BP_Implementation(const FInputActionValue& Value) {}

void AMain::Func_Attack_Start_BP_Implementation() {}

void AMain::Func_Attack_End_BP_Implementation() {}

// Attack
void AMain::Func_Attack_Start()
{
	if (bStanding)
	{
		bAttack = true;
		/*
		if (Pistol_Montage)
		{
			UAnimInstance* AnimInstance = Pistol->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_Play(Pistol_Montage, 1.f);
				AnimInstance->Montage_JumpToSection(FName("Attack"), Pistol_Montage);
			}
		}
		*/
		Func_Attack_Start_BP();
	}
}

void AMain::Func_Standing_Start()
{
	bStanding = true;
}

void AMain::Func_Standing_End(const FInputActionValue& Value)
{
	bStanding = false;
	bAttack = false;
}

void AMain::Func_Attack_End()
{
	bAttack = false;
	/*
	if (Pistol_Montage)
	{
		UAnimInstance* AnimInstance = Pistol->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(Pistol_Montage, 1.f);
			AnimInstance->Montage_JumpToSection(FName("Attack_End"), Pistol_Montage);
		}
	}
	*/
	Func_Attack_End_BP();
}

void AMain::Rotate_Reverse_Start(const FInputActionValue& Value)
{
	if (fRotate_Reverse == 1.f)
	{
		fRotate_Reverse = -1.f;
	}
}

void AMain::Rotate_Reverse_End(const FInputActionValue& Value)
{
	if (fRotate_Reverse == -1.f)
	{
		fRotate_Reverse = 1.f;
	}
}