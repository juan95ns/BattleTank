// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player: %s"), *(PlayerTank->GetName()));
	}
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (!GetControlledTank()) { return;  }
	else 
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const 
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) 
	{
		return nullptr;
	}
	else 
	{
		return Cast<ATank>(PlayerPawn);
	}
}

