// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
//forward Declaration
class UTankBarrel; 
class UTankTurret;
//Holds Barrels properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS2_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Gets the Barrel Reference
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	// Gets the Turret Reference
	void SetTurretReference(UTankTurret* TurretToSet);


	void AimAt(FVector HitLocation, float LaunchSpeed);
private:

	void MoveBarrelTowards(FVector AimDirection);
	/*
	void MoveTurretTowards(FVector AimDirection);
	*/

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = FiringArc)
	bool HighLowArc = false;

};
