// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectNextListItem.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_SelectNextListItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		if (Individual->ShoppingList.IsValidIndex(0))
		{
			EAisleType nextItemToBuy = Individual->ShoppingList[0];
			Controller->SetListItem(nextItemToBuy);
			Individual->ShoppingList.RemoveAt(0);
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}