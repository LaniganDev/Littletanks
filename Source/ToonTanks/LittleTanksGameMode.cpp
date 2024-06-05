// Fill out your copyright notice in the Description page of Project Settings.


#include "LittleTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "LittleTanksPlayerController.h"
#include "Mine.h"

void ALittleTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(LittleTanksPlayerController)
        {
            LittleTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
        
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if (TargetTowers == 0)
        {
            GameOver(true);
        }
    }
    else if (AMine* DestroyedMine = Cast<AMine>(DeadActor))
    {
        DestroyedMine->HandleDestruction();
        GameOver(false);
    }
    
}

void ALittleTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();


}

void ALittleTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics:: GetPlayerPawn(this,0));
    LittleTanksPlayerController = Cast<ALittleTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

    StartGame();

    if(LittleTanksPlayerController)
    {
        LittleTanksPlayerController->SetPlayerEnabledState(false);

        //Creates & Handles GameTimer
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            LittleTanksPlayerController,
            &ALittleTanksPlayerController::SetPlayerEnabledState,
            true);
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false);
    }
}

int32 ALittleTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();

}
