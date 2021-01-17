// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectHUD.h"
#include "MyProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MainPlayerController.h"

AMyProjectGameMode::AMyProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_Player"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AMainPlayerController> PlayerControllerClassFinder(TEXT("/Game/GameSettings/BP_MainPlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
	// use our custom HUD class
	//HUDClass = NULL;
}
