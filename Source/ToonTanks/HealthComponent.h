// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	float GetCurrentHealth() const {return Health;}
	float GetMaxHealth() const {return MaxHealth;}
	float SetNewHealth(float NewHealth) {return Health = FMath::Clamp(NewHealth,0,MaxHealth);}


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

private:
	UPROPERTY(EditANywhere)
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere)
	float Health = 0.f;

	class ALittleTanksGameMode* LittleTanksGameMode;
		
};
