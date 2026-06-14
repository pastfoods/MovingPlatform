// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "CH3_3PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetSimulatePhysics(false);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	SkeletalMeshComponent->SetSimulatePhysics(false);

	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	MoveSpeed = 100.0f;
	RotationSpeed = 1.0f;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
 	{
		if (ACH3_3PlayerController* PlayerController = Cast<ACH3_3PlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APlayerPawn::Move);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APlayerPawn::Look);
			}
		}
	}
}

void APlayerPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	const FVector2D MoveInput = value.Get<FVector2D>();
	
	FVector MoveForward = GetActorForwardVector();
	FVector MoveRight = GetActorRightVector();
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddActorWorldOffset(MoveInput.X*MoveForward*MoveSpeed*DeltaTime,true);

	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddActorWorldOffset(MoveInput.Y*MoveRight*MoveSpeed*DeltaTime,true);

	}
}

void APlayerPawn::Look(const FInputActionValue& value)
{
	if (!Controller) return;
	const FVector2D LookInput = value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		AddActorLocalRotation(FRotator(0.0f,LookInput.X*RotationSpeed,0.0f),true);
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		//SpringArm의 현재 Pitch를 가져와서 입력값만큼 더하고, 범위를 제한한 뒤 다시 적용"**
		FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
		NewRotation.Pitch += LookInput.Y*RotationSpeed;
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch,-80.0f,80.0f);
		SpringArmComponent->SetRelativeRotation(NewRotation);
	}
}
