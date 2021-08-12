// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BuyItem.h"

#include "Till.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_BuyItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividual* Individual;
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		//Controller->SetIsSelling(true);

		int shoppingListSize = Individual->ShoppingList.Num();
		if (shoppingListSize > 0)
		{
			Individual->ShoppingList.RemoveAt(shoppingListSize - 1);

			return EBTNodeResult::Succeeded;
		}
		else
		{
			Individual->SetIsInQueue(false);
			Controller->SetIsSelling(false);

			ATill* Till = Controller->GetTill();
			Till->LeaveQueue(Individual);

			Controller->SetIsShopping(false);
			Controller->SetHasFinishedSelling(true);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}