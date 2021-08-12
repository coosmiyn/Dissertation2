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

	OnEndPlay.AddDynamic(this, &ADissertationGameMode::EndPlay);
}

//TArray<AActor*> ADissertationGameMode::GetSortedAisles()
//{
//	TArray<AActor*> allAisleActors;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAisle::StaticClass(), allAisleActors);
//
//	TArray<AActor*> entrance;
//}

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

void ADissertationGameMode::IncreaseCollision(EBuyingState state)
{
	if (state == EBuyingState::Explore)
		NumOfExploreCollisions++;
	else if (state == EBuyingState::FastBuy)
		NumOfFastCollisions++;
}

void ADissertationGameMode::SaveData(FString name, EBuyingState state, int numOfCollisions, int listSize, FTimespan timeSpent)
{
	Names.Add(name);
	States.Add(state);
	NumOfCollisions.Add(numOfCollisions);
	ListSize.Add(listSize);
	TimeSpent.Add(timeSpent);
}

void ADissertationGameMode::EndPlay(AActor* actor, const EEndPlayReason::Type EndPlayReason)
{
	GEngine->AddOnScreenDebugMessage(23524, 300.0f, FColor::MakeRandomColor(), TEXT("EXPLORE/FAST COLLISIONS"));
	GEngine->AddOnScreenDebugMessage(23525, 300.0f, FColor::MakeRandomColor(), FString::FromInt(NumOfExploreCollisions));
	GEngine->AddOnScreenDebugMessage(23526, 300.0f, FColor::MakeRandomColor(), FString::FromInt(NumOfFastCollisions));
}
