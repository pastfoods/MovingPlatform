// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "ActivatablePlatform.h"
// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnCount = 5;

}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();	
	SpawnPlatform();
}

// Called every frame

void APlatformSpawner::SpawnPlatform()
{
	for (int32 i =0;i<SpawnCount;i++)
	{
		FVector RLocation = FVector(FMath::RandRange(0.0f,1500.0f),FMath::RandRange(0.0f,1500.0f),10.0f);
		AActivatablePlatform* SpawnedPlatform= GetWorld()->SpawnActor<AActivatablePlatform>(Platform,RLocation,FRotator::ZeroRotator);
		if (SpawnedPlatform)
		{
			SpawnedPlatform->SetMaxRange(FMath::RandRange(500.0f,1500.0f));
			SpawnedPlatform->SetMinRange(FMath::RandRange(0.0f,SpawnedPlatform->GetMaxRange()));
			SpawnedPlatform->SetMoveSpeed(FMath::RandRange(50.0f,200.0f));
			SpawnedPlatform->SetRotationSpeed(FMath::RandRange(30.0f,180.0f));
			SpawnedPlatform->SetTeleportEnabled(FMath::RandBool());
			SpawnedPlatform->SetBlinkEnabled(FMath::RandBool());
		}
		
	}
}
