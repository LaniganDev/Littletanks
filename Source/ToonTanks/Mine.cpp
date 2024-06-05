// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"
#include "Tank.h"
#include "HealthComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(50.f);
	RootComponent = CollisionSphere;
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMine::OnOverlapBegin);

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
    
	MineMesh->SetupAttachment(RootComponent);



}

void AMine::HandleDestruction()
{
	Destroy();
}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if ( OtherActor && OtherActor != this)
    {
        // Check if the overlapping actor is a projectile
        AProjectile* Projectile = Cast<AProjectile>(OtherActor);
        if (Projectile)
        {

            // Apply damage to the mine
            UHealthComponent* HealthComp = Cast<UHealthComponent>(FindComponentByClass<UHealthComponent>());
            if (HealthComp)
            {
                UGameplayStatics::ApplyDamage(this, Projectile->Damage, nullptr, this, nullptr);
                
			}
            // Destroy the projectile
            Projectile->Destroy();
        }
		if (OtherActor && OtherActor != this && !Projectile)
		{
			UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, nullptr, this, nullptr);
			Destroy();

		}

        // Debug log
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Mine Overlapped by: %s"), *OtherActor->GetName()));
        }
    }
}

