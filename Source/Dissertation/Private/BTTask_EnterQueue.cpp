// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EnterQueue.h"

#include "Kismet/GameplayStatics.h"
#include "Till.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_EnterQueue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Failed;
}