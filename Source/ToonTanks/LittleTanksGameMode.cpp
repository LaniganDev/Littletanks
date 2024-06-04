// Fill out your copyright notice in the Description page of Project Settings.


#include "LittleTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "LittleTanksPlayerController.h"

void ALittleTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(LittleTanksPlayerController)
        {
            LittleTanksPlayerController->SetPlayerEnabledState(false);
        }
        
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }
    
}

void ALittleTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics:: GetPlayerPawn(this,0));
    LittleTanksPlayerController = Cast<ALittleTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
}
