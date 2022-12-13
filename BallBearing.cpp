// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearing.h"

// Sets default values
ABallBearing::ABallBearing()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetSimulatePhysics(true);
	SetRootComponent(BallMesh);
	BallMesh->SetLinearDamping(0.5f);
	BallMesh->SetAngularDamping(0.5f);
}

void ABallBearing::ResetLocation()
{
	BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	BallMesh->SetWorldLocation(InitialLocation + FVector(0, 0, 150.f));
}

void ABallBearing::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = BallMesh->GetComponentLocation();
}

void ABallBearing::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	bInContact = false;
}


