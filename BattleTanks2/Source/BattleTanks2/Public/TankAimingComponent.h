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
//Holds Barrels properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS2_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// TODO add SetTurretReference

	void AimAt(FVector HitLocation, float LaunchSpeed);
private:

	void MoveBarrelTowards(FVector AimDirection);


	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = FiringArc)
	bool HighLowArc = false;

};
