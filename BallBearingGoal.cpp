// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearingGoal.h"
#include "Components/ShapeComponent.h"
#include "Components/BillboardComponent.h"
#include <Components/SphereComponent.h>

ABallBearingGoal::ABallBearingGoal()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorHiddenInGame(false);
}

void ABallBearingGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetCollisionComponent()->bHiddenInGame = true;
#if WITH_EDITORONLY_DATA
	if(GetSpriteComponent() != nullptr) GetSpriteComponent()->bHiddenInGame = true;
#endif
}

void ABallBearingGoal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ABallBearing* BallBearing = Cast<ABallBearing>(OtherActor);
	if (BallBearing != nullptr && BallBearing->bMagnetized == true)
	{
		BallBearings.AddUnique(BallBearing);
	}
}

void ABallBearingGoal::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	ABallBearing* BallBearing = Cast<ABallBearing>(OtherActor);
	if (BallBearing != nullptr && BallBearing->bMagnetized == true)
	{
		BallBearings.Remove(BallBearing);
	}
}

float GetRatio(float Value, float Min, float Max, bool bClamp = true)
{
	if (Value > Max && bClamp == true)
	{
		return 1.f;
	}
	else if (Value > Min)
	{
		return (Value - Min) / (Max - Min);
	}
	else
	{
		return 0;
	}
}

void ABallBearingGoal::BeginPlay()
{
	Super::BeginPlay();
	OurLocation = GetActorLocation();
	SphereRadius = Cast<USphereComponent>(GetCollisionComponent())->GetScaledSphereRadius();
}

void ABallBearingGoal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	for (ABallBearing* BallBearing : BallBearings)
	{
		FVector BallLocation = BallBearing->BallMesh->GetComponentLocation();
		FVector Displacement = OurLocation - BallLocation;
		float Distance = Displacement.Size();
		FVector Direction = Displacement;
		Direction.Normalize();
		float Ratio = (1.f - GetRatio(Distance, 0, SphereRadius)); // 0 when Ball bearing is outside Sphere, 1 when it is exactly at center of Sphere. Ratio increases linearly as ball bearing comes closed to center of Sphere!
		FVector MagneticForce = Ratio * Magnetism * Direction * 100.f;
		BallBearing->BallMesh->AddForce(MagneticForce);
	}
}

bool ABallBearingGoal::HasBallBearing()
{
	for (ABallBearing* BallBearing : BallBearings)
	{
		FVector BallLocation = BallBearing->GetActorLocation();
		float Distance = (OurLocation - BallLocation).Size();
		if (Distance < SphereRadius)
		{
			return true;
		}
	}
	return false;
}