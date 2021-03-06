// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

UCLASS()
class TILEFIGHTERS_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Tile Functions")
	void CreateMesh(UStaticMesh* Mesh);

	UFUNCTION(BlueprintCallable, Category = "Tile Functions")
	void SpawnFighter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Components")
	UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Components")
	bool isTeam1Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Components")
	bool isTeam2Spawn;
};
