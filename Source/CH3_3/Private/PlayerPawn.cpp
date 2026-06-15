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
	PrimaryActorTick.bCanEverTick = true;

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
	
	Gravity = -980.0f;
	VerticalVelocity= 0;	
	MoveSpeed = 100.0f;
	RotationSpeed = 1.0f;
	RollSpeed = 4.0f;
	FlySpeed = 300.0f;
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
	const FVector MoveInput = value.Get<FVector>();
	
	FVector MoveForward = FVector(MoveInput.X*CurrentMoveSpeed*DeltaTime,0.0f,0.0f);
	FVector MoveRight = FVector(0.0f,MoveInput.Y*CurrentMoveSpeed*DeltaTime,0.0f);
	FVector MoveUp = FVector(0.0f,0.0f,MoveInput.Z*FlySpeed*DeltaTime);
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddActorLocalOffset(MoveForward,true);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddActorLocalOffset(MoveRight,true);
	}
	if (!FMath::IsNearlyZero(MoveInput.Z))
	{
		AddActorLocalOffset(MoveUp,true);
	}
}

void APlayerPawn::Look(const FInputActionValue& value)
{
	if (!Controller) return;
	const FVector LookInput = value.Get<FVector>();
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
		UE_LOG(LogTemp, Warning, TEXT("SpringArm Pitch: %f"), NewRotation.Pitch);
	}
	
	if (!FMath::IsNearlyZero(LookInput.Z))
	{
		AddActorLocalRotation(FRotator(0.0f,0.0f, LookInput.Z*RollSpeed),true);
	}
	UE_LOG(LogTemp, Warning, TEXT("LookInput: X=%f Y=%f Z=%f"), LookInput.X, LookInput.Y, LookInput.Z);

}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CheckGroundCollision())
	{
		VerticalVelocity = 0;
		CurrentMoveSpeed = MoveSpeed;
	}
	else
	{
		VerticalVelocity += Gravity * DeltaTime;
		CurrentMoveSpeed = MoveSpeed * 0.5;
		AddActorWorldOffset(FVector(0, 0, VerticalVelocity * DeltaTime), true);
	}
}

bool APlayerPawn::CheckGroundCollision()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.0f,0.0f,1.0f);
	
	FCollisionShape Shape = FCollisionShape::MakeCapsule(CapsuleComponent->GetScaledCapsuleRadius(),CapsuleComponent->GetScaledCapsuleHalfHeight());
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat(GetActorRotation()),
		ECC_Visibility,
		Shape,
		Params);
	
	return bHit;
}
