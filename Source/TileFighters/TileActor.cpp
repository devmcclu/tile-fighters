// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor.h"
#include "FighterPawn.h"

// Sets default values
ATileActor::ATileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));

}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnFighter();
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATileActor::CreateMesh(UStaticMesh* Mesh)
{
	TileMesh->SetStaticMesh(Mesh);
}

void ATileActor::SpawnFighter()
{
	if (isTeam1Spawn || isTeam2Spawn)
	{
		FVector spawnLocation = GetActorLocation() + (GetActorUpVector() * 150.0f) + (GetActorRightVector() * -50.0f) + (GetActorForwardVector() * -50.0f);

		FRotator spawnRotation = FRotator();

		FActorSpawnParameters spawnParameters;
		spawnParameters.Instigator = GetInstigator();
		spawnParameters.Owner = this;

		GetWorld()->SpawnActor<AFighterPawn>(spawnLocation, spawnRotation, spawnParameters);
	}
}
