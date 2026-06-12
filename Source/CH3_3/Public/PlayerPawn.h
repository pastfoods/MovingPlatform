// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;



UCLASS()
class CH3_3_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pawn")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pawn")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera")
	UCameraComponent* CameraComponent;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
