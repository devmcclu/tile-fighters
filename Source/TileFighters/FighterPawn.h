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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Health for the fighter
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	int CurrentHealth;

	// Max health for the fighter
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int MaxHealth;

	/* Attack value for the fighter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Values")
	int AttackValue; */
	
	// Stamina for the fighter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	int Stamina;

	// RepNotify for changes made to current health
	UFUNCTION()
	void OnRep_CurrentHealth();

	// Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify
	void OnHealthUpdate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/* UFUNCTION(BlueprintCallable, Category = "Tile Functions")
	void Damage(int DamageAmount); */

	/** Getter for Max Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE int GetMaxHealth() const { return MaxHealth; }

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE int GetCurrentHealth() const { return CurrentHealth; }

	/** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(int healthValue);

	/** Event for taking damage. Overridden from APawn.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Sphere component used to test collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereComponent;

	// Static Mesh used to provide a visual representation of the object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	//The damage type and damage that will be done by this projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<class UDamageType> DamageType;

	//The damage dealt by this projectile.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;

	//The damage dealt by this projectile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	int Team;

	// New postion to move to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector newLocation;
};
