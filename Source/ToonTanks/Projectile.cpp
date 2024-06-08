// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
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

	SmokeTrialParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trial Particles"));
	SmokeTrialParticles->SetupAttachment(RootComponent);
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
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
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
	if(HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
	}
	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
	}
	if(HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
	// Destroy the projectile
	Destroy();
}





