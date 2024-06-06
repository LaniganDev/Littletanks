// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}


void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    UHealthComponent* HealthComponent = FindComponentByClass<UHealthComponent>();
    if(HealthComponent-> GetCurrentHealth() >= 50.f)
    {
        FVector DeltaLocation = FVector::ZeroVector;
        // X = Value * DeltaTime * Speed
        DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
        AddActorLocalOffset(DeltaLocation, true);
    }
    else
    {
        FVector DeltaLocation = FVector::ZeroVector;
        // X = Value * DeltaTime * Speed
        DeltaLocation.X = Value * DamagedSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
        AddActorLocalOffset(DeltaLocation, true);
    }
    
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // Yaw = Value * DeltaTime * TurnRate
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
    GetController();
}
void ATank::Fire()
{
    if (GetCurrentAmmo() > 0)
    {
        SetCurrentAmmo(GetCurrentAmmo() -1);
        Super::Fire(); // Call the base class Fire method
    }
    else
    {
        
        UE_LOG(LogTemp, Warning, TEXT("Out of Ammo!"));
    }
}
