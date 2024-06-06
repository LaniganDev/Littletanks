// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "Mine.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	// Ensure that the attached FieldSystemActor follows the projectile
	if (AttachedFieldSystemActor)
	{
		AttachedFieldSystemActor->SetActorLocation(GetActorLocation());
	}
	
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* Hitcomp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	 if (OtherActor && OtherActor != this && OtherComp)
    {
        {
            // Apply damage to the other actor (if it's not the mine)
            auto MyOwner = GetOwner();
            if (MyOwner)
            {
                auto MyOwnerInstigator = MyOwner->GetInstigatorController();
                auto DamageTypeClass = UDamageType::StaticClass();
                UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
            }
        }
    }
	// Check if FieldSystemActorToSpawn is set
	if (FieldSystemActorToSpawn)
	{
		// Spawn the Field System Actor
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AttachedFieldSystemActor = GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

		// Attach the FieldSystemActor to the projectile's root component
		if (AttachedFieldSystemActor)
		{
			AttachedFieldSystemActor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
	// Delay the destruction of the field system to allow it to complete its task
	if (AttachedFieldSystemActor)
	{
		FTimerHandle TimerHandle;
		float DestructionDelay = 3.0f; // Adjust the delay as needed
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			if (AttachedFieldSystemActor && !AttachedFieldSystemActor->IsPendingKill())
			{
				AttachedFieldSystemActor->Destroy();
			}
		}, DestructionDelay, false);
	}
	// Destroy the projectile
	Destroy();
}





