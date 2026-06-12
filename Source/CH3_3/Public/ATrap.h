// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATrap.generated.h"

UCLASS()
class CH3_3_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trap")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trap")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trap")
	float RotationSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trap")
	float MoveSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trap")
	float MaxRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trap")
	float MinRange;
	bool bDirection;
	
	UFUNCTION(BlueprintCallable)
	void Move(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void Spin(float DeltaTime);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
