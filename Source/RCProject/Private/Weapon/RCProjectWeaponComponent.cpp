// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RCProjectWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/RCProjectBaseWeapon.h"

// Sets default values for this component's properties
URCProjectWeaponComponent::URCProjectWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}




// Called when the game starts
void URCProjectWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void URCProjectWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ARCProjectBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmetRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmetRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);

}

void URCProjectWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}
