// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h" //Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void AimTowardsCrosshair();

	// Return an Out Parameter, get true if hits landscape
	bool GetCrossHairTraceHit(FString& ObjectHit, FVector& HitLocation) const;


	UPROPERTY(EditAnyWhere)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnyWhere)
		float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnyWhere)
		float LineTraceRange = 1000000;
	
	
};
