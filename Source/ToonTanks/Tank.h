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

public:
	int32 GetCurrentAmmo() const { return Ammo; }
	int32 GetMaxAmmo() const { return MaxAmmo; }
	void SetCurrentAmmo(int32 NewAmmo) { Ammo = FMath::Clamp(NewAmmo, 0, MaxAmmo); }

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


	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
};
