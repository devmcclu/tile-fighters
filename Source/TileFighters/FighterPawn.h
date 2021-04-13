// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FighterPawn.generated.h"

UCLASS()
class TILEFIGHTERS_API AFighterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFighterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Health for the fighter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Components")
	int32 health;

	// Attack value for the fighter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Components")
	int32 attackValue;
	
	// Stamina for the fighter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Components")
	int32 stamina;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Tile Functions")
	void Damage(int32 damageAmount);
};
