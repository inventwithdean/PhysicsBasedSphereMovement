// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBallBearing.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerBallBearing::APlayerBallBearing()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bMagnetized = false;
}


static void InitializeDefaultPawnInputBindings()
{
	static bool bBindingsAdded = false;
	if (bBindingsAdded) return;
	bBindingsAdded = true;
	UE_LOG(LogTemp, Warning, TEXT("Adding Bindings!"))
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_LookUp", EKeys::MouseY, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_LookRight", EKeys::MouseX, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::W, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::S, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::A, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::D, 1.f));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Jump", EKeys::SpaceBar));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Dash", EKeys::LeftShift));
}

void APlayerBallBearing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InitializeDefaultPawnInputBindings();
	PlayerInputComponent->BindAxis("BallBearing_LookUp", this, &APlayerBallBearing::LookUp);
	PlayerInputComponent->BindAxis("BallBearing_LookRight", this, &APlayerBallBearing::LookRight);
	PlayerInputComponent->BindAxis("BallBearing_MoveLongitudinally", this, &APlayerBallBearing::MoveLongitudinally);
	PlayerInputComponent->BindAxis("BallBearing_MoveLaterally", this, &APlayerBallBearing::MoveLaterally);
	PlayerInputComponent->BindAction("BallBearing_Jump", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Jump);
	PlayerInputComponent->BindAction("BallBearing_Dash", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Dash);
}

void APlayerBallBearing::Jump()
{
	if (bInContact)
	{
		BallMesh->AddImpulse(FVector(0, 0, 1.f) * JumpForce * 100.f);
	}
}

void APlayerBallBearing::Dash()
{
	if (DashTimer == 0)
	{
		FVector Velocity = BallMesh->GetComponentVelocity();
		if (Velocity.Size() > 100.f)
		{
			Velocity.Normalize();
			Velocity *= DashForce * 100.f;
			BallMesh->AddImpulse(Velocity);
			DashTimer = 1.15f;
		}
	}
}

void APlayerBallBearing::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FRotationMatrix ControlMatrix = FRotationMatrix(ControlRotation);
	FVector ForwardDirection = ControlMatrix.GetUnitAxis(EAxis::X);
	FVector RightDirection = ControlMatrix.GetUnitAxis(EAxis::Y);

	FVector Velocity = BallMesh->GetPhysicsLinearVelocity();
	float Z = Velocity.Z;
	if (Velocity.Size() > MaximumSpeed * 100.f) // Maximum Speed is in m/s
	{
		Velocity.Normalize();
		Velocity *= MaximumSpeed * 100.f;
		Velocity.Z = Z;
		float BrakingRatio = FMath::Pow((1 - FMath::Min(DashTimer, 1.f)), 2); // 0 when when just started dashing, 1 when not dashing!
		FVector MergedVelocity = FMath::Lerp(BallMesh->GetPhysicsLinearVelocity(), Velocity, BrakingRatio);
		BallMesh->SetPhysicsLinearVelocity(MergedVelocity);
	}
	else
	{
		BallMesh->AddForce((InputLatitude * RightDirection + InputLongitude * ForwardDirection) * ControllerForce * BallMesh->GetMass());
	}
	if (DashTimer > 0)
	{
		DashTimer = FMath::Max(0, DashTimer - DeltaSeconds);
	}
}