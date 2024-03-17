// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RCProjectBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


// Sets default values
ARCProjectBaseWeapon::ARCProjectBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

// Called when the game starts or when spawned
void ARCProjectBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);



}


void ARCProjectBaseWeapon::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("Fire"));
    MakeShot();
}
void ARCProjectBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FVector TraceStartRight, TraceEndRight;
    if (!GetTraceDataRight(TraceStartRight, TraceEndRight)) return;

    FVector TraceStartLeft, TraceEndLeft;
    if (!GetTraceDataLeft(TraceStartLeft, TraceEndLeft)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FHitResult HitResultRight;
    MakeHitRight(HitResultRight, TraceStartRight, TraceEndRight);

    FHitResult HitResultLeft;
    MakeHitLeft(HitResultLeft, TraceStartLeft, TraceEndLeft);
   

    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

        UE_LOG(LogTemp, Display, TEXT("Impact: %s"), *HitResult.ImpactPoint.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);
        UE_LOG(LogTemp, Display, TEXT("TraceEnd: %s"), *TraceEnd.ToString());
    }

    if (HitResultRight.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResultRight.ImpactPoint, FColor::Blue, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResultRight.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);

        UE_LOG(LogTemp, Display, TEXT("Impact: %s"), *HitResultRight.ImpactPoint.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEndRight, FColor::Yellow, false, 3.0f, 0, 3.0f);
        UE_LOG(LogTemp, Display, TEXT("TraceEnd: %s"), *TraceEndRight.ToString());
    }

    if (HitResultLeft.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResultLeft.ImpactPoint, FColor::Purple, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResultLeft.ImpactPoint, 10.0f, 24, FColor::Purple, false, 5.0f);

        UE_LOG(LogTemp, Display, TEXT("Impact: %s"), *HitResultLeft.ImpactPoint.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEndLeft, FColor::Cyan, false, 3.0f, 0, 3.0f);
        UE_LOG(LogTemp, Display, TEXT("TraceEnd: %s"), *TraceEndLeft.ToString());
    }

}

APlayerController* ARCProjectBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();

}

bool ARCProjectBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ARCProjectBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ARCProjectBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + (ShootDirection * TraceMaxDistance);
    return true;

}

bool ARCProjectBaseWeapon::GetTraceDataRight(FVector& TraceStartRight, FVector& TraceEndRight) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    float AngleInRadiansRight = 45.0f * PI / 180.0f;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) false;

    TraceStartRight = ViewLocation;
   const FVector TraceDirectionRight = ViewRotation.RotateVector(FVector(cos(AngleInRadiansRight), sin(AngleInRadiansRight), 0));
    TraceEndRight = TraceStartRight + (TraceDirectionRight * TraceMaxDistance);
    return true;

}

bool ARCProjectBaseWeapon::GetTraceDataLeft(FVector& TraceStartLeft, FVector& TraceEndLeft) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    float AngleInRadiansLeft = -45.0f * PI / 180.0f;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) false;

    TraceStartLeft = ViewLocation;
    const FVector TraceDirectionLeft = ViewRotation.RotateVector(FVector(cos(AngleInRadiansLeft), sin(AngleInRadiansLeft), 0));
    TraceEndLeft = TraceStartLeft + (TraceDirectionLeft * TraceMaxDistance);
    return true;

}

void ARCProjectBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ARCProjectBaseWeapon::MakeHitRight(FHitResult& HitResultRight, const FVector& TraceStartRight, const FVector& TraceEndRight)
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResultRight, TraceStartRight, TraceEndRight, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ARCProjectBaseWeapon::MakeHitLeft(FHitResult& HitResultLeft, const FVector& TraceStartLeft, const FVector& TraceEndLeft)
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResultLeft, TraceStartLeft, TraceEndLeft, ECollisionChannel::ECC_Visibility, CollisionParams);
}