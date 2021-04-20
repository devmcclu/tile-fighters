// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPlayerController.h"

AFighterPlayerController::AFighterPlayerController()
{
	// Allow the pawn to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFighterPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AFighterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
