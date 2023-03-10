// Copyright Epic Games, Inc. All Rights Reserved.


#include "RCProjectGameModeBase.h"
#include "Player/RCProjectCharacter.h"
#include "Player/RCProjectPlayerController.h"
#include "UI/RCProjectHUD.h"


ARCProjectGameModeBase::ARCProjectGameModeBase() 
{
	DefaultPawnClass = ARCProjectCharacter::StaticClass();
	PlayerControllerClass = ARCProjectPlayerController::StaticClass();
	HUDClass = ARCProjectHUD::StaticClass();
}