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

FString ADissertationGameMode::EnumToString(const TCHAR* Enum, int32 EnumValue) const
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
	if (!EnumPtr)
		return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

#if WITH_EDITOR
	return EnumPtr->GetDisplayNameText(EnumValue).ToString();
#else
	return EnumPtr->GetEnumName(EnumValue);
#endif
}
