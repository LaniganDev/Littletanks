// Fill out your copyright notice in the Description page of Project Settings.


#include "LMine.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "HealthComponent.h"

// Sets default values
ALMine::ALMine()
{
 	 PrimaryActorTick.bCanEverTick = false;

    MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
    RootComponent = MineMesh;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);
    CollisionSphere->InitSphereRadius(50.f);
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ALMine::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALMine::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALMine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	 if (OtherActor && OtherActor != this)
    {
        ATank* Tank = Cast<ATank>(OtherActor);
        if (Tank)
        {
            UHealthComponent* HealthComp = Cast<UHealthComponent>(Tank->GetComponentByClass(UHealthComponent::StaticClass()));
            if (HealthComp)
            {
                HealthComp->DamageTaken(Tank, DamageAmount, nullptr, nullptr, this);
                Destroy();
            }
        }
    }
}


