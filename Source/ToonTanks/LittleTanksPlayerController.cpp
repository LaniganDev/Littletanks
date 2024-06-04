// Fill out your copyright notice in the Description page of Project Settings.


#include "LittleTanksPlayerController.h"
#include "Gameframework/Pawn.h"

void ALittleTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}


