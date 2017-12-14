// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possesing: %s"), *(ControlledTank->GetName()));
	}
	Super::BeginPlay();
}

void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Parameter
	FString ObjectHit = "Nothing";
	if (GetCrossHairTraceHit(ObjectHit, HitLocation))
	{ 
		
		//Tell controlled Tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetCrossHairTraceHit(FString& ObjectHit, FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairPosition = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//Seguido por https://community.gamedev.tv/t/unreal-provides-a-much-simpler-way-to-accomplish-all-of-this/2557
	//En vez de la lectura 131, de esta forma es mucho mas simple
	FHitResult HitResult;
	bool bHit = GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_WorldStatic, false, HitResult);
	
	if (bHit)
	{
		HitLocation = HitResult.Location;
		ObjectHit = HitResult.GetActor()->GetName();
	}

	return bHit;
}
