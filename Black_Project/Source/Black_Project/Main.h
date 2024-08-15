// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Main.generated.h"

UCLASS()
class BLACK_PROJECT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	AMain();

	// Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Capsule_Hand")
	class UCapsuleComponent* Capsule_Hand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pistol")
	class USkeletalMeshComponent* Pistol;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Offset_UD")
	float OffsetUpDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wepon_UD")
	float WeponUpDown;

	float Lock_U_Rate;

	float Lock_R_Rate;

	// Air
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "bIsInAir")
	bool Main_bIsInAir;

	// Movement


	// Contelloer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class APlayerController_Main* MainPlayerController;

	// Attack
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotate_Reverse")
	float fRotate_Reverse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Standing")
	bool bStanding;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OJ")
	bool bOJ;

	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pistol | Pistol_Montage")
	class UAnimMontage* Pistol_Montage;
	*/

protected:
	virtual void BeginPlay() override;

	// Inpute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* IA_MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_LookInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Standing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_JumpInpute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Rotate_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Rotate_P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Rotate_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Space;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Rotate_Reverse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* InputMapping;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera
	void Look(const FInputActionValue& Value);

	// Air


	// Movement
	void Move(const FInputActionValue& Value);

	// BlueprintImplementableEvent BlueprintNativeEvent
	// Attack
	UFUNCTION(BlueprintNativeEvent, Category = "F_Attack_S")
	void Func_Attack_Start_BP();
	virtual void Func_Attack_Start_BP_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "F_Attack_E")
	void Func_Attack_End_BP();
	virtual void Func_Attack_End_BP_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Rotate_R")
	void Rotate_R_BP(const FInputActionValue& Value);
	virtual void Rotate_R_BP_Implementation(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Rotate_P")
	void Rotate_P_BP(const FInputActionValue& Value);
	virtual void Rotate_P_BP_Implementation(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Rotate_Y")
	void Rotate_Y_BP(const FInputActionValue& Value);
	virtual void Rotate_Y_BP_Implementation(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Func_Standing_End")
	void Func_Standing_End_BP(const FInputActionValue& Value);
	virtual void Func_Standing_End_BP_Implementation(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Func_Space")
	void Func_Space_BP(const FInputActionValue& Value);
	virtual void Func_Space_BP_Implementation(const FInputActionValue& Value);

	void Func_Attack_Start();
	void Func_Standing_Start();
	void Func_Standing_End(const FInputActionValue& Value);
	void Func_Attack_End();
	void Rotate_Reverse_Start(const FInputActionValue& Value);
	void Rotate_Reverse_End(const FInputActionValue& Value);
};
