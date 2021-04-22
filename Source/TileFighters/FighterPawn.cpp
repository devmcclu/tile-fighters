// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AFighterPawn::AFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MaxHealth = 1;
	CurrentHealth = MaxHealth;

    DamageType = UDamageType::StaticClass();
    Damage = 1.0f;

    //Definition for the SphereComponent that will serve as the Root component for the projectile and its collision.
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    SphereComponent->InitSphereRadius(37.5f);
    SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    RootComponent = SphereComponent;

    //Definition for the Mesh that will serve as our visual representation.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMesh->SetupAttachment(RootComponent);

    //Set the Static Mesh and its position/scale if we successfully found a mesh asset to use.
    if (DefaultMesh.Succeeded())
    {
        StaticMesh->SetStaticMesh(DefaultMesh.Object);
        StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -37.5f));
        StaticMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
    }
}

void AFighterPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFighterPawn, CurrentHealth);
}

// Called when the game starts or when spawned
void AFighterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFighterPawn::OnRep_CurrentHealth()
{
    OnHealthUpdate();
}

void AFighterPawn::OnHealthUpdate()
{
    // Client - specific functionality
        if (IsLocallyControlled())
        {
            FString healthMessage = FString::Printf(TEXT("You now have %d health remaining."), CurrentHealth);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

            if (CurrentHealth <= 0)
            {
                FString deathMessage = FString::Printf(TEXT("You have been killed."));
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
            }
        }

    //Server-specific functionality
    if (GetLocalRole() == ROLE_Authority)
    {
        FString healthMessage = FString::Printf(TEXT("%s now has %d health remaining."), *GetFName().ToString(), CurrentHealth);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
    }

    //Functions that occur on all machines. 
    /*
        Any special functionality that should occur as a result of damage or death should be placed here.
    */
}

// Called every frame
void AFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/* void AFighterPawn::Damage(int32 damageAmount)
{
	CurrentHealth -= damageAmount;
	if (CurrentHealth <= 0)
	{
		Destroy();
	}
} */

void AFighterPawn::SetCurrentHealth(int healthValue)
{
    if (GetLocalRole() == ROLE_Authority)
    {
        CurrentHealth = FMath::Clamp(healthValue, 0, MaxHealth);
        OnHealthUpdate();
    }
}

float AFighterPawn::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float damageApplied = CurrentHealth - DamageTaken;
    SetCurrentHealth(damageApplied);
    return damageApplied;
}

