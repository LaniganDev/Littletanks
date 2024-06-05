// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LittleTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ALittleTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:

	class ATank* Tank;
	class ALittleTanksPlayerController* LittleTanksPlayerController;
	
	float StartDelay = 3.f;

	void HandleGameStart();
};
