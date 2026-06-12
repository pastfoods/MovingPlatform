// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatablePlatform.h"

#include "WorldPartition/ContentBundle/ContentBundleLog.h"

// Sets default values
AActivatablePlatform::AActivatablePlatform()
{	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MatarialAsset(TEXT("/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Worn.M_Wood_Floor_Walnut_Worn"));
	if (MatarialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0,MatarialAsset.Object);
	}
	
	MoveSpeed = 130.0f;
	RotationSpeed = 120.0f;
	MinRange =-350.0f;
	MaxRange = 550.0f;
	bMoveDirection = true;
	bMoveEnabled = true;
	bRotateEnabled = true;
	bTeleportEnabled = true;
	bTeleportDirection = true;
	bBlinkEnabled = true;
	bIsActive = true;
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActivatablePlatform::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Teleport,this,&AActivatablePlatform::Teleport,1.0f,true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Blink,this,&AActivatablePlatform::Blink,5.0f,true);

}

// Called every frame
void AActivatablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Spin(DeltaTime);
}


void AActivatablePlatform::SetMaxRange(float Range)
{
	MaxRange = Range;
}

void AActivatablePlatform::SetMinRange(float Range)
{
	MinRange = Range;
}

void AActivatablePlatform::SetMoveSpeed(float Speed)
{
	MoveSpeed = Speed;
}

void AActivatablePlatform::SetRotationSpeed(float Speed)
{
	RotationSpeed = Speed;
}

void AActivatablePlatform::SetBlinkEnabled(bool Check)
{
	bBlinkEnabled = Check;
}

void AActivatablePlatform::SetTeleportEnabled(bool Check)
{
	bTeleportEnabled = Check;
}

float AActivatablePlatform::GetMaxRange() const
{
	return MaxRange;
}


void AActivatablePlatform::Move(float DeltaTime)
{
	if (!bMoveEnabled)
	{
		return;
	}
	if (!FMath::IsNearlyZero(MoveSpeed))
	{
		FVector NewLocation = GetActorLocation();
		if (bMoveDirection)
		{
			NewLocation.Y += MoveSpeed * DeltaTime;
			SetActorLocation(NewLocation);
			if (NewLocation.Y >= MaxRange)
			{
				bMoveDirection=!bMoveDirection;
			}
		}
		else
		{
			NewLocation.Y -= MoveSpeed * DeltaTime;
			SetActorLocation(NewLocation);
			if (NewLocation.Y <= MinRange)
			{
				bMoveDirection=!bMoveDirection;
			}
		}
	}
}

void AActivatablePlatform::Spin(float DeltaTime)
{	
	if (!bRotateEnabled)
	{
		return;
	}
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f,RotationSpeed * DeltaTime,0.0f));
	}
}
void AActivatablePlatform::Teleport()
{
	if (bTeleportEnabled)
	{
		FVector NewLocation = GetActorLocation();
		if (bTeleportDirection)
		{
			NewLocation.X +=200.0f;
		}
		else
		{
			NewLocation.X -=200.0f;
		}
		bTeleportDirection = !bTeleportDirection;
		SetActorLocation(NewLocation);
	}
}

void AActivatablePlatform::Blink()
{
	if (bBlinkEnabled)
	{
		bIsActive = !bIsActive;

		if (bIsActive)
		{
			StaticMeshComp->SetVisibility(true);
			StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			StaticMeshComp->SetVisibility(false);
			StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
		}
	}
}
