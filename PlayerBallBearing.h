// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallBearing.h"
#include "PlayerBallBearing.generated.h"

/**
 * 
 */
UCLASS()
class APlayerBallBearing : public ABallBearing
{
	GENERATED_BODY()
public:
	APlayerBallBearing();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float ControllerForce = 450.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float JumpForce = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float DashForce = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float MaximumSpeed = 5.f;
private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera = nullptr;
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
private:
	void LookUp(float Value)
	{
		AddControllerPitchInput(Value);
	}
	void LookRight(float Value)
	{
		AddControllerYawInput(Value);
	}
	void MoveLongitudinally(float Value)
	{
		InputLongitude = Value;
	}
	void MoveLaterally(float Value)
	{
		InputLatitude = Value;
	}
	void Jump();
	void Dash();
	float DashTimer = 0;
	float InputLongitude = 0;
	float InputLatitude = 0;
	friend class ABallBearingHUD;
};
