// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Aisle.h"
#include "STypes.h"
#include "Kismet/GameplayStatics.h"

#include "DissertationGameMode.generated.h"

UCLASS(minimalapi)
class ADissertationGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADissertationGameMode();

    FString EnumToString(const TCHAR* Enum, int32 EnumValue) const;

	//TArray<AActor*> GetSortedAisles();

	void IncreaseCollision(EBuyingState state);

	void SaveData(FString name, EBuyingState state, int numOfCollisions, int listSize, FTimespan timeSpent);

	UFUNCTION()
	void EndPlay(AActor* actor, const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int NumOfExploreCollisions;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int NumOfFastCollisions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<FString> Names;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<EBuyingState> States;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<int> NumOfCollisions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<int> ListSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<FTimespan> TimeSpent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<AActor*> IndividualReferences;
};



