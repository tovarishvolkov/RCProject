// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RCProjectHUD.generated.h"

/**
 * 
 */
UCLASS()
class RCPROJECT_API ARCProjectHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;

private:

	void DrawCrossHair(); 
	
};
