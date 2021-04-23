// Copyright Epic Games, Inc. All Rights Reserved.

#include "DissertationGameMode.h"
#include "DissertationPlayerController.h"
#include "DissertationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADissertationGameMode::ADissertationGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADissertationPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}