// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivatablePlatform.generated.h"

UCLASS()
class CH3_3_API AActivatablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivatablePlatform();
	void SetMoveSpeed(float Speed);
	void SetRotationSpeed(float Speed);
	void SetMaxRange(float Range);
	void SetMinRange(float Range);
	void SetBlinkEnabled(bool Check);
	void SetTeleportEnabled(bool Check);
	float GetMaxRange() const;


protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	float RotationSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	float MoveSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	float MaxRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	float MinRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	bool bMoveEnabled;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	bool bRotateEnabled;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	bool bTeleportEnabled;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	bool bBlinkEnabled;
	
	bool bMoveDirection;
	bool bTeleportDirection;
	bool bIsActive;
	FTimerHandle TimerHandle_Teleport; 
	FTimerHandle TimerHandle_Blink; 

	void Move(float DeltaTime);
	void Spin(float DeltaTime);
	void Teleport();
	void Blink();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
