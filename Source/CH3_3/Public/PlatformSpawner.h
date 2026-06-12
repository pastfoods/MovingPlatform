// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class AActivatablePlatform;

UCLASS()
class CH3_3_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Platform")
	TSubclassOf<AActivatablePlatform> Platform;
	int32 SpawnCount;
	
	virtual void BeginPlay() override;
	void SpawnPlatform();
};
