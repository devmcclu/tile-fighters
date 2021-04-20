// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterPawn.h"
#include "GameFramework/PlayerController.h"
#include "FighterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TILEFIGHTERS_API AFighterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Constructor
	AFighterPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFighterPawn* CurrentFighterPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AFighterPawn*> FighterPawnList;
};
