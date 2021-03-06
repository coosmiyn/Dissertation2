// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "Individual.h"

#include "BTTask_ChooseNextAisle.generated.h"

/**
 * 
 */
UCLASS()
class DISSERTATION_API UBTTask_ChooseNextAisle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void SortAisles(TArray<AActor*> aisles, AIndividual* individual);
};
