// Fill out your copyright notice in the Description page of Project Settings.


#include "ATrap.h"

// Sets default values
ATrap::ATrap()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Traps/Saw.Saw"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Metal_Copper.M_Metal_Copper"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0,MaterialAsset.Object);
	}
	MoveSpeed = 130.0f;
	RotationSpeed = 180.0f;
	PrimaryActorTick.bCanEverTick = true;
	MinRange =-350.0f;
	MaxRange = 550.0f;
	bDirection = true;
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(210.0f,100.0f,150.0f));
	SetActorRotation(FRotator(90.0f,0.0f,0.0f));
	SetActorScale3D(FVector(2.0f));
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Spin(DeltaTime);

}

void ATrap::Move(float DeltaTime)
{
	if (!FMath::IsNearlyZero(MoveSpeed))
	{
		FVector NewLocation = GetActorLocation();
		if (bDirection)
		{
			NewLocation.Y += MoveSpeed * DeltaTime;
			SetActorLocation(NewLocation);
			if (NewLocation.Y >= MaxRange)
			{
				bDirection=false;
			}
		}
		else
		{
			NewLocation.Y -= MoveSpeed * DeltaTime;
			SetActorLocation(NewLocation);
			if (NewLocation.Y <= MinRange)
			{
				bDirection=true;
			}
		}
	}
}

void ATrap::Spin(float DeltaTime)
{	
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f,0.0f,RotationSpeed * DeltaTime));
	}
}
