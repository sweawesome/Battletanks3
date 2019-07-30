// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;

}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

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

		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time)
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time)
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)// start location socket should point in the direction of AimDirection 
{
	// find the difference in aim direction vs start location direction

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	

		Barrel->Elevate(DeltaRotator.Pitch); // Remove "magic" number
}