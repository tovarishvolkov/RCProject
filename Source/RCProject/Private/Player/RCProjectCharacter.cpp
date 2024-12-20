// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RCProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARCProjectCharacter::ARCProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void ARCProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARCProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARCProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARCProjectCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ARCProjectCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ARCProjectCharacter::TurnAround);
}

void ARCProjectCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ARCProjectCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ARCProjectCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ARCProjectCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

