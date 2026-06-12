// Fill out your copyright notice in the Description page of Project Settings.


#include "CH3_3GameMode.h"
#include "PlayerPawn.h"
#include "CH3_3PlayerController.h"
ACH3_3GameMode::ACH3_3GameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = ACH3_3PlayerController::StaticClass();
}
