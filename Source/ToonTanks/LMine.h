// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "LMine.generated.h"

UCLASS()
class TOONTANKS_API ALMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MineMesh;

    UPROPERTY(VisibleAnywhere)
	 USphereComponent* CollisionSphere;

    UPROPERTY(EditAnywhere)
    float DamageAmount = 50.f;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
