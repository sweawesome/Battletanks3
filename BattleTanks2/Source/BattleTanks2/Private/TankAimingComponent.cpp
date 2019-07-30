// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector HitLoc = HitLocation;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Looks for a socket inside of the UObject barrel and gets its location
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // All parameters that should be optional are not, and should not be deleted.
	);
	
	if (bHaveAimSolution) // Calculate the OutLaunchVelocity
	{ 
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // gets the OutLaunchVelocity's normal i.e turns it in to a unit vector
		MoveBarrelTowards(AimDirection);
		//MoveTurretTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time)
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time)
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)// start location socket should point in the direction of AimDirection 
{
	// find the difference in aim direction vs start location direction

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("BarrelDeltaRot: %s"), *BarrelDeltaRotator.ToString())
	
		Barrel->Elevate(BarrelDeltaRotator.Pitch);
		Turret->Rotate(BarrelDeltaRotator.GetNormalized().Yaw);
}
/*
void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)// start location socket should point in the direction of AimDirection 
{
	// find the difference in aim direction vs start location direction

	auto AimAsRotator = AimDirection.Rotation();
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto TurretDeltaRotator = AimAsRotator - TurretRotator;
	UE_LOG(LogTemp, Warning, TEXT("TurretDeltaRot: %s"), *TurretDeltaRotator.ToString())

	Turret->Rotate(TurretDeltaRotator.Yaw);

}
*/