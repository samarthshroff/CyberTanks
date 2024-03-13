// Fill out your copyright notice in the Description page of Project Settings.


#include "CyberTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "CyberTanksPlayerController.h"
#include "TimerManager.h"

void ACyberTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();

}

void ACyberTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (CyberTanksPlayerController)
        {
            CyberTanksPlayerController->SetPlayerEnabledState(false);
            GameOver(false);
        }
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;
        if (TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void ACyberTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    CyberTanksPlayerController = Cast <ACyberTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (CyberTanksPlayerController)
    {
        CyberTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(CyberTanksPlayerController, &ACyberTanksPlayerController::SetPlayerEnabledState, true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
}

int32 ACyberTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}