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
    PlayerInputComponent->BindAction(TEXT("UseHealth"),IE_Pressed,this,&ATank::UseHealth);
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
    bAlive = false;
}


void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    UHealthComponent* HealthComponent = FindComponentByClass<UHealthComponent>();
    float CurrentHealth = HealthComponent->GetCurrentHealth();
    
    FVector DeltaLocation = FVector::ZeroVector;

    if (CurrentHealth <= DamageState2) // Tank is critically damaged
    {

        return;
    }
    else if (CurrentHealth <= DamageState1) // Tank is damaged but not critically
    {
        // Move at reduced speed
        DeltaLocation.X = Value * DamagedSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
    }
    else // Tank is not damaged
    {
        // Move at full speed
        DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    }

    AddActorLocalOffset(DeltaLocation, true);
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
void ATank::UseHealth()
{
    if (bHasHealthPickup)
    {
        UHealthComponent* HealthComp = FindComponentByClass<UHealthComponent>();
        if (HealthComp)
        {
            float CurrentHealth = HealthComp->GetCurrentHealth();
            float MaxHealth = HealthComp->GetMaxHealth();
            
            // Check if health is less than max health before attempting to increase it
            if (CurrentHealth < MaxHealth)
            {
                float NewHealth = FMath::Clamp(CurrentHealth + PickupAmount, 0.0f, MaxHealth);
                HealthComp->SetNewHealth(NewHealth);
                currentHealthPickups--; // Decrease health pickups only if health is increased
                if (currentHealthPickups <= 0)
                {
                    bHasHealthPickup = false;
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Health is already at maximum!"));
            }
            
            return;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Health component not found!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No health pickup available!"));
    }
}


