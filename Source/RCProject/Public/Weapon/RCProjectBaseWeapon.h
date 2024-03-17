// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RCProjectBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class RCPROJECT_API ARCProjectBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARCProjectBaseWeapon();

	virtual void Fire();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TraceAngle = 45.0f;


	virtual void BeginPlay() override;

	void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	bool GetTraceDataRight(FVector& TraceStartRight, FVector& TraceEndRight) const;
	bool GetTraceDataLeft(FVector& TraceStartLeft, FVector& TraceEndLeft) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void MakeHitRight(FHitResult& HitResultRight, const FVector& TraceStartRight, const FVector& TraceEndRight);
	void MakeHitLeft(FHitResult& HitResultLeft, const FVector& TraceStartLeft, const FVector& TraceEndLeft);
};
