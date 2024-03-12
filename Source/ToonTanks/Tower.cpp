// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CheckIfTankWithinFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::CheckFireCondition()
{
    if (CheckIfTankWithinFireRange())
    {
        Fire();
    }
}

bool ATower::CheckIfTankWithinFireRange()
{
    if (Tank)
    {
        if (!Tank->bAlive)
        {
            return false;
        }

        FVector TankLocation = Tank->GetActorLocation();
        float Distance = FVector::Dist(GetActorLocation(), TankLocation);
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}