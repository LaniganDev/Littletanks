// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups.h"
#include "Components/StaticMeshComponent.h"
#include "Tank.h"

// Sets default values
APickups::APickups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(30.f);
	RootComponent = CollisionSphere;
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, & APickups::OnOverlapBegin);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp Mesh"));
	PickupMesh->SetupAttachment(RootComponent);
	


}

// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickups::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ATank* Tank = Cast<ATank>(OtherActor);
	if(Tank)
	{
		int32 CurrentAmmo = Tank->GetCurrentAmmo();
		int32 MaxAmmo = Tank->GetMaxAmmo();
		int32 NewAmmo = FMath::Clamp(CurrentAmmo+AmmoPickup,0,MaxAmmo);
		Tank->SetCurrentAmmo(NewAmmo);
		Destroy();
	}
	return;
}

