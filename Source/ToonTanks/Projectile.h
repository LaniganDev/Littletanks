// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Field/FieldSystemActor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* Hitcomp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category="Comabat")
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* SmokeTrialParticles;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<AFieldSystemActor> FieldSystemActorToSpawn;
	

	// Reference to the spawned FieldSystemActor
	AFieldSystemActor* AttachedFieldSystemActor;

};
