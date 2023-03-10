// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RCProjectWeaponComponent.generated.h"

class USkeletalMeshComponent;
class ARCProjectBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RCPROJECT_API URCProjectWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URCProjectWeaponComponent();

	void Fire();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponAttachPointName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<ARCProjectBaseWeapon> WeaponClass;
	
	virtual void BeginPlay() override;

private:

	UPROPERTY()
		ARCProjectBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
		
};
