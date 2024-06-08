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
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const {return TankPlayerController;}



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Fire() override;
	void UseHealth();

public:
	int32 GetCurrentAmmo() const { return Ammo; }
	int32 GetMaxAmmo() const { return MaxAmmo; }
	void SetCurrentAmmo(int32 NewAmmo) { Ammo = FMath::Clamp(NewAmmo, 0, MaxAmmo); }

	bool bHasHealthPickup = false;
	void SetPickupAmount(float Amount) { PickupAmount = Amount; }
	int32 GetCurrentHealthPickups() const {return currentHealthPickups;}
	int32 GetMaxHealthPickups() const {return maxHealthPickup;}
	void SetCurrentHealthPickups(int32 NewHealthPickups) {currentHealthPickups = FMath::Min(NewHealthPickups, maxHealthPickup);
	}
	
	

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 700.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DamagedSpeed = 700.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f;

	UPROPERTY(EditAnywhere)
	int32 Ammo = 10;
	int32 MaxAmmo = 10;

	float PickupAmount = 0.f;
	UPROPERTY(EditAnywhere)
	int32 maxHealthPickup =2;
	UPROPERTY(VisibleAnywhere)
	int32 currentHealthPickups = 0;

	float DamageState1 = 50.f;
	float DamageState2 = 25.f;
	
	void Move(float Value);
	void Turn(float Value);

	bool bHasEmergencyHealthApplied = false;

	APlayerController* TankPlayerController;
};
