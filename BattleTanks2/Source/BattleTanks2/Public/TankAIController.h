// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS2_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
