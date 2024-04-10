// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameplayTagContainer.h"
#include "BasePawn.generated.h"

USTRUCT(BlueprintType)
struct FRateOfFire
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int NumberOfBullets;

	UPROPERTY(EditAnywhere)
	float Interval;

	// Reload time - return from Fire function if >= reloadtime
	// Cooldown time - start accepting fire function after cooldown reaches 0 - countdown timer
	//use these 2 timers to show UI (Gun hot and cooldown) bar
};


UCLASS()
class CYBERTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectTileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
	bool IsFiring;
	FTimerHandle FireRateTimerHandle;

	int32 PendingProjectileToFire;

private:
	void FireProjectile();

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TMap < FGameplayTag, FRateOfFire> RateOfFire;

	// For now hardcoding this from the BP editor.
	// This value will come from Inventory and current weapon selected.
	UPROPERTY(EditAnywhere, Category = "Combat")
	FGameplayTag CurrentProjectile;
};
