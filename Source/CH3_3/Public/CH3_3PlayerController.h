// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CH3_3PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
UCLASS()
class CH3_3_API ACH3_3PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACH3_3PlayerController();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* LookAction;
protected:
	virtual void BeginPlay() override;
};
