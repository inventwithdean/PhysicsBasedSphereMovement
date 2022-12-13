// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "BallBearing.h"

#include "BallBearingGoal.generated.h"

/**
 * 
 */
UCLASS()
class ABallBearingGoal : public ATriggerSphere
{
	GENERATED_BODY()
public:
	ABallBearingGoal();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Magnetism")
	float Magnetism = 5000.f;
	bool HasBallBearing();
protected:
	void PostInitializeComponents() override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
private:
	UPROPERTY(Transient)
	TArray<ABallBearing*> BallBearings;
	float SphereRadius = 100.f;
	FVector OurLocation;
};
