// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
<<<<<<< HEAD
#include "TimerManager.h"
=======
>>>>>>> origin/main

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

<<<<<<< HEAD
    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
=======
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        
        if( Distance <= FireRange)
        {
            RotateTurret(Tank->GetActorLocation());    //if in range rotate turret toward tank
        }
        
    }

>>>>>>> origin/main
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

<<<<<<< HEAD
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if (InFireRange())
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }

    return false;
=======
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
>>>>>>> origin/main
}