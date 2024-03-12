// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float Value);

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 100.0f;

	APlayerController* TankPlayerController;

public:
	bool bAlive = true;
};
