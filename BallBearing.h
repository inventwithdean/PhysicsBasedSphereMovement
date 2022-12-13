// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallBearing.generated.h"

UCLASS()
class ABallBearing : public APawn
{
	GENERATED_BODY()

public:
	ABallBearing();
	UPROPERTY(VisibleAnywhere, Category = BallBearing)
	class UStaticMeshComponent* BallMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	bool bMagnetized = true;
	UFUNCTION(BlueprintCallable)
	void ResetLocation();
protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override
	{
		Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
		bInContact = true;
	}
	bool bInContact = false;
private:
	FVector InitialLocation = FVector::ZeroVector;
	friend class ABallBearingHUD;
};
