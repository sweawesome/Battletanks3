// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



class ATank;

UCLASS()
class BATTLETANKS2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:

	void AimTowardsCrosshair(); // Start the tank moving the barrel so that a shot would hit where the crosshair itersects the world.

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5,
		CrosshairYLocation = 0.3333; // maby change this to 0.6666 if i'm wright about it

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLoc, FVector& LookDirection) const; 

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};


