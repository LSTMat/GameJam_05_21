// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJam_052021GameMode.h"
#include "GameJam_052021HUD.h"
#include "GameJam_052021Character.h"
#include "UObject/ConstructorHelpers.h"

AGameJam_052021GameMode::AGameJam_052021GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGameJam_052021HUD::StaticClass();
}
